#include "sql/stmt/alter_column_drop_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
RC AlterColumnDropStmt::create(Db *db,const AlterColumnDropSqlNode &alter_column_drop ,Stmt *&stmt ){
  stmt=new AlterColumnDropStmt(alter_column_drop.relation_name,alter_column_drop.attribute_name);
  if(stmt==nullptr){
    LOG_WARN("Failed to create AlterColumnDrop. file:%s, line:%d\n",
  __FILE__,__LINE__);
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}
