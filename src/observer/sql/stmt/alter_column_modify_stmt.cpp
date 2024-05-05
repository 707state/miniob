#include "sql/stmt/alter_column_modify_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
RC AlterColumnModifyStmt::create(Db *db, const AlterColumnModifySqlNode &alter_column_modify, Stmt *&stmt)
{
  stmt = new AlterColumnModifyStmt(alter_column_modify.relation_name, alter_column_modify.attr_infos);
  if (stmt == nullptr) {
    LOG_WARN("Failed to create AlterColumnModifyStmt. file:%s, line:%d\n",
  __FILE__,__LINE__);
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}
