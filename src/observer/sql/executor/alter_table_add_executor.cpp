#include "sql/executor/alter_table_add_executor.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"

#include "sql/stmt/alter_table_add_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
RC AlterTableAddExecuter::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type()==StmtType::ALTER_INDEX_ADD,
	"alter table add executor can not run this commoand:%d",
	static_cast<int>(stmt->type()) );
  AlterTableAddStmt *alter_table_add = static_cast<AlterTableAddStmt *>(stmt);
  const char        *table_name      = alter_table_add->table_name().c_str();
  const char        *index_name      = alter_table_add->index_name().c_str();
  const char        *attribute_name  = alter_table_add->attribute_name().c_str();
  if (common::is_blank(table_name) || common::is_blank(index_name) || common::is_blank(attribute_name)) {
    LOG_WARN("Unrecognized info. table(%s), index_name(%s), attribute_name(%s), file(%s), line(%d)",
		         table_name,index_name,attribute_name,__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  Trx *trx = session->current_trx();
  if (trx == nullptr) {
    LOG_WARN("trx is null. file(%s), line(%d)",__FILE__,__LINE__);
    return RC::GENERIC_ERROR;
  }
  Table *table = alter_table_add->table();
  if (table == nullptr) {
    LOG_WARN("Null table(%s) at FILE(%s), LINE(%d)",
             table_name,__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  const FieldMeta *field_meta = alter_table_add->field_meta();
  if (field_meta == nullptr) {
    LOG_WARN("field_meta (%s) not existing. file(%s), line(%d)",
             field_meta->name(),__FILE__,__LINE__);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  return table->create_index(trx, field_meta, index_name);
}
