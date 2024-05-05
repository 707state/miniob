#include "sql/stmt/alter_table_modify_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
#include "common/rc.h"
#include "storage/field/field_meta.h"
#include "storage/index/index.h"
using namespace common;
RC AlterTableModifyStmt::create(Db *db, const AlterIndexModifySqlNode &alter_table_modify, Stmt *&stmt)
{
  stmt                       = nullptr;
  std::string table_name     = alter_table_modify.relation_name;
  std::string index_name     = alter_table_modify.index_name;
  std::string attribute_name = alter_table_modify.attribute_name;
  if (is_blank(table_name.c_str()) || is_blank(index_name.c_str()) || is_blank(attribute_name.c_str())) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s, attribute_name=%s, file=%s, line=%d",
  db,table_name.c_str(),index_name.c_str(),attribute_name.c_str(),__FILE__,__LINE__);
    return RC::INVALID_ARGUMENT;
  }
  Table *table = db->find_table(table_name.c_str());
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s, file=%s, line=%d",
	db->name(),table_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  const FieldMeta *field_meta = table->table_meta().field(index_name.c_str());
  if (field_meta != nullptr) {
    LOG_WARN("field for index_name(%s) already in table. db=%s, table=%s, field_name=%s, file=%s, line=%d",
 index_name.c_str(),db->name(),table_name.c_str(),attribute_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }
  Index *index = table->find_index(index_name.c_str());
  if (index == nullptr) {
    LOG_WARN("attribute index with name(%s) not exist. table_name=%s, index_name=%s, file=%s, line=%d",
  table_name.c_str(),index_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  stmt = new AlterTableModifyStmt(table, field_meta, table_name, index_name, attribute_name);
  return RC::SUCCESS;
}
