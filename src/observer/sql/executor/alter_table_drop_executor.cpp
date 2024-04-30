#include "sql/executor/alter_table_drop_executor.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/alter_table_drop_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
RC AlterTableDropExecuter::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type()==StmtType::ALTER_TABLE_DROP,
  "create index executor can not run this command: %d",static_cast<int>(stmt->type()) );
  AlterTableDropStmt *alter_table_drop_stmt = static_cast<AlterTableDropStmt *>(stmt);
  Trx *trx=session->current_trx(); 
  Db                 *t                     = session->get_current_db();
  const char         *table_name            = alter_table_drop_stmt->table_name().c_str();
  const char         *index_name            = alter_table_drop_stmt->index_name().c_str();
  Table              *table                 = t->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("Failed to find table(%s) in db(%s), file(%s), line(%d)",table_name,t->name(),__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  const FieldMeta *field_meta=table->table_meta().field(index_name);
  if(field_meta==nullptr){
    LOG_WARN("Failed to find field with index_name(%s).\nFILE:%s, LINE:%d",
             table_name,__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  return table->drop_index(trx,index_name,field_meta);
}
