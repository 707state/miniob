#include "sql/stmt/alter_column_add_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
RC AlterColumnAddStmt::create(Db *db,const AlterColumnAddSqlNode& alter_column_add ,Stmt *&stmt ){
  stmt=new AlterColumnAddStmt(alter_column_add.relation_name,alter_column_add.attr_infos);
  if(stmt==nullptr){
    LOG_WARN("Failed to create AlterColumnAdd. file:%s, line:%d\n",
  __FILE__,__LINE__);
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}
