#include "sql/executor/alter_column_add_executor.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/alter_column_add_stmt.h"
#include "storage/field/field.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"
#include "sql/stmt/select_stmt.h"
#include <string>
#include <type_traits>
// static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
// {
//   const TableMeta &table_meta = table->table_meta();
//   const int        field_num  = table_meta.field_num();
//   for (int i = table_meta.sys_field_num(); i < field_num; i++) {
//     field_metas.push_back(Field(table, table_meta.field(i)));
//   }
// }


RC AlterColumnAddExecutor::execute(SQLStageEvent *sql_event){
  Stmt *stmt=sql_event->stmt();
  Session *session=sql_event->session_event()->session();
  ASSERT(stmt->type()==StmtType::ALTER_COLUMN_ADD,
         "alter column add command not executing. file:%s, line:%d\n",
         __FILE__,__LINE__ );
  AlterColumnAddStmt *alter_column_add_stmt=static_cast<AlterColumnAddStmt*>(stmt);
  //获取需要建立的表的信息
  const std::string& table_name=alter_column_add_stmt->table_name();
  auto& attri_infos=alter_column_add_stmt->attr_infos();
  //获取之前的表的信息
  // Db *db=session->get_current_db();
  Table *table=session->get_current_db()->find_table(table_name.c_str());
  TableMeta &old_table_meta=table->table_meta();
  std::vector<AttrInfoSqlNode> old_attri_infos=old_table_meta.attr_infos();
 old_attri_infos.insert(std::end(old_attri_infos),std::begin(attri_infos),std::end(attri_infos));
RC rc= old_table_meta.init(table->table_id(),table_name.c_str() ,old_attri_infos.size() ,old_attri_infos.data() );
if(rc!=RC::SUCCESS){
  LOG_WARN("Unable to re-init. table:%s.",table_name.c_str());
  return rc;
}  
  return RC::SUCCESS;
}
