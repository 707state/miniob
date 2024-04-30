#include "sql/stmt/alter_table_drop_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/drop_index_stmt.h"
#include "storage/db/db.h"
#include "common/rc.h"
#include "storage/index/index.h"
#include "storage/table/table.h"
using namespace common;
RC AlterTableDropStmt::create(Db *db, const AlterDropSqlNode &alter_table_drop, Stmt *&stmt)
{
  stmt                   = nullptr;
  std::string table_name = alter_table_drop.relation_name;
  std::string index_name = alter_table_drop.index_name;
  if (is_blank(table_name.c_str()) || is_blank(index_name.c_str())) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index_name=%s, file=%s, line=%d",
  db,table_name.c_str(),index_name.c_str(),__FILE__,__LINE__);
    return RC::INVALID_ARGUMENT;
  }
  Table *table = db->find_table(table_name.c_str());
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s, file=%s, line=%d",db->name(),table_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  Index *index = table->find_index(index_name.c_str());
  if (index == nullptr) {
    LOG_WARN("index with name(%s) not exists. table name=%s, file=%s, line=%d",
  index_name.c_str(),table_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_INDEX_NOT_EXIST;
  }
  const FieldMeta *field_meta=table->table_meta().field(index_name.c_str());
  // if(field_meta!=nullptr){
  //   LOG_WARN("field does not have index(%s)",index_name.c_str());
  //   return RC::SCHEMA_FIELD_NOT_EXIST;
  // }
  stmt = new AlterTableDropStmt(table,field_meta, index_name);
  return RC::SUCCESS;
}
