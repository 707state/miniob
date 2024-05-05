#include "sql/executor/alter_column_drop_executor.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/alter_column_drop_stmt.h"
RC AlterColumnDropExecutor::execute(SQLStageEvent *sql_event)
{
  Session *session = sql_event->session_event()->session();
  Stmt    *stmt    = sql_event->stmt();
  ASSERT(stmt->type()==StmtType::ALTER_COLUMN_DROP,
  "alter column drop command not executing. file: %s, line:%d\n",
  __FILE__,__LINE__ );
  AlterColumnDropStmt *alter_column_drop_stmt = static_cast<AlterColumnDropStmt *>(stmt);
  const std::string   &table_name             = alter_column_drop_stmt->table_name();
  const std::string   &attribute_name         = alter_column_drop_stmt->attribute_name();
  RC rc = session->get_current_db()->find_table(table_name.c_str())->table_meta().remove_column(attribute_name);
  if (rc != RC::SUCCESS) {
    LOG_WARN("Unable to remove column(%s) in table(%s).",
    attribute_name.c_str(),table_name.c_str());
    return rc;
  }
  return RC::SUCCESS;
}
