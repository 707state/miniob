#include "sql/stmt/alter_table_add_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "sql/parser/parse_defs.h"
#include "common/rc.h"
#include "storage/field/field_meta.h"
#include "storage/index/index.h"
#include "storage/table/table.h"
using namespace common;
RC AlterTableAddStmt::create(Db *db,const AlterAddSqlNode &alter_table_add ,Stmt *&stmt ){
  stmt=nullptr;
  auto table_name=alter_table_add.relation_name;
  auto index_name=alter_table_add.index_name;
  auto attribute_name=alter_table_add.attribute_name;
  if(is_blank(table_name.c_str())||is_blank(index_name.c_str())||is_blank(attribute_name.c_str())){
    LOG_WARN("invalid argument. db=%p, table_name=%s, index_name=%s,attribute_name=%s,file=%s,line=%d",
  db,table_name.c_str(),index_name.c_str(),attribute_name.c_str(),__FILE__,__LINE__);
    return RC::INVALID_ARGUMENT;
  }
  Table *table=db->find_table(table_name.c_str());
  if(table==nullptr){
    LOG_WARN("no such table. db=%s, table_name=%s, file=%s, line=%d",db->name(),table_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  const FieldMeta *field_meta=table->table_meta().field(alter_table_add.attribute_name.c_str());
  if(field_meta==nullptr){
    LOG_WARN("no such field in table. db=%s, table=%s, attribute_name=%s, file=%s, line=%d",
  db->name(),table_name.c_str(),alter_table_add.attribute_name.c_str(),__FILE__,__LINE__);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  //Index name? Attribute name?
  //find if index exists
  Index *index=table->find_index(index_name.c_str());
  if(index!=nullptr){
    LOG_WARN("index with name(%s) already exists. table name=%s, file=%s, line=%d",
 index_name.c_str(),table_name.c_str(),__FILE__,__LINE__ );
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }
  stmt=new AlterTableAddStmt(table,field_meta,table_name.c_str(),index_name.c_str(),attribute_name.c_str());
  return RC::SUCCESS;
  
}
