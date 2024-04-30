#include "sql/executor/drop_index_executor.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "sql/stmt/drop_index_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field_meta.h"
#include "session/session_stage.h"
#include "storage/table/table.h"
#include "session/session.h"
#include "session/session_stage.h"
#include "event/session_event.h"
RC DropIndexExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  ASSERT(stmt->type()==StmtType::DROP_INDEX,
  "create table executor can not run this command: %d",
  static_cast<int>(stmt->type()) );
  DropIndexStmt *drop_index_stmt = static_cast<DropIndexStmt *>(stmt);
  Session *session=sql_event->session_event()->session();
  Table         *table           = drop_index_stmt->table();
  Trx *trx=session->current_trx();
  if (table == nullptr) {
    LOG_WARN("no table(%s). file=%s, line=%d",
			  table->name(),__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  return table->drop_index(trx,drop_index_stmt->index_name().c_str(),drop_index_stmt->field_meta());
}
