#include "sql/executor/alter_table_modify_executor.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/alter_table_modify_stmt.h"
#include "storage/field/field_meta.h"
RC AlterTableModifyExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type()==StmtType::ALTER_INDEX_MODIFY,
  "alter table modidy executor can not run this command: %d",
  static_cast<int>(stmt->type()) );
  AlterTableModifyStmt *alter_table_modify_stmt = static_cast<AlterTableModifyStmt *>(stmt);
  Trx                  *trx                     = session->current_trx();
  Table                *table                   = alter_table_modify_stmt->table();
  const char           *index_name              = alter_table_modify_stmt->index_name().c_str();
  const char           *attribute_name          = alter_table_modify_stmt->attribute_name().c_str();
  const FieldMeta *field_meta                   = alter_table_modify_stmt->field_meta();
  RC                    rc                      = table->drop_index(trx,index_name,field_meta);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to drop index(%s) on db(%s), file(%s), line(%d)",
  index_name,session->get_current_db_name(),__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  rc = table->create_index(trx, alter_table_modify_stmt->field_meta(), attribute_name);
  if (rc != RC::SUCCESS) {
    LOG_WARN("create index(%s) on db(%s) failed. file(%s), line(%d)",
  attribute_name,session->get_current_db_name(),__FILE__,__LINE__);
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}
