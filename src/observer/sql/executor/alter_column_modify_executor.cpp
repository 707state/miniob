#include "sql/executor/alter_column_modify_executor.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/executor/alter_table_modify_executor.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/alter_table_modify_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/alter_column_modify_stmt.h"
#include <gtest/gtest.h>
RC AlterColumnModifyExecutor::execute(SQLStageEvent *sql_event){
  Session *session=sql_event->session_event()->session();
  Stmt *stmt=sql_event->stmt();
  ASSERT(stmt->type()==StmtType::ALTER_COLUMN_MODIFY,
         "Can not execute the alter column modify command" );
  AlterColumnModifyStmt *alter_column_modify=static_cast<AlterColumnModifyStmt*>(stmt);
  std::string table_name=alter_column_modify->table_name();
  std::vector<AttrInfoSqlNode> attri_infos=alter_column_modify->attr_infos();
  Table *table=session->get_current_db()->find_table(table_name.c_str());
  for(auto attr_info:attri_infos){
    table->table_meta().remove_column(attr_info.name.c_str());
  }
  std::vector<AttrInfoSqlNode> old_attri_infos=table->table_meta().attr_infos();
  old_attri_infos.insert(std::end(old_attri_infos),std::begin(attri_infos),std::end(attri_infos));
  RC rc=table->table_meta().init(table->table_id(),table_name.c_str() ,old_attri_infos.size() ,old_attri_infos.data() );
  if(rc!=RC::SUCCESS){
    LOG_WARN("Unable to modify table(%s).",table_name.c_str());
    return rc;
  }
  return RC::SUCCESS;
}
