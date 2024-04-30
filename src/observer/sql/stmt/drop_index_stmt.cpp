#include "sql/stmt/drop_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
// #include "storage/field/field_meta.h"
#include "storage/field/field_meta.h"
#include "storage/index/index.h"
#include <cstddef>
using namespace common;
RC DropIndexStmt::create(Db *db, const DropIndexSqlNode &drop_index, Stmt *&stmt)
{
  stmt                   = nullptr;
  const char *table_name = drop_index.relation_name.c_str();
  if (common::is_blank(table_name) || is_blank(drop_index.index_name.c_str())) {
    LOG_WARN("invalid arguments. db=%p, table_name=%p, index_name=%s, file=%s, line=%d",
  db,table_name,drop_index.index_name.c_str(),__FILE__,__LINE__);
    return RC::INVALID_ARGUMENT;
  }
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such field in table. db=%p, table_name=%s, file=%s, line=%d",
  db,table_name,__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  Index *index = table->find_index(drop_index.index_name.c_str());
  if (index == nullptr) {
    LOG_WARN("index with name(%s) doesn't exist. table name=%s, file=%s, line=%d",
  drop_index.index_name.c_str(),table_name,__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  const FieldMeta *field_meta = table->table_meta().field(drop_index.index_name.c_str());
  if (field_meta == nullptr) {
    LOG_WARN("field_meta (%s). table name(%s), file(%s), line(%d)",field_meta->name(),table_name
			  ,__FILE__,__LINE__);
    return RC::SCHEMA_FIELD_MISSING;
  }
  stmt = new DropIndexStmt(table, field_meta, drop_index.index_name);
  return RC::SUCCESS;
}
