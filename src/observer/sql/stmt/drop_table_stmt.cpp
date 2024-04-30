#include "sql/stmt/drop_table_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt)
{
  stmt = new DropTableStmt(drop_table.relation_name);
  //sql_debug(
    //  "drop table statement: table name %s, file=%s, line=%d", drop_table.relation_name.c_str(), __FILE__, __LINE__);
    if(stmt==nullptr){
      LOG_WARN("drop table statement: table_name %s, file=%s, line=%d",
    drop_table.relation_name.c_str(),__FILE__,__LINE__);
      return RC::GENERIC_ERROR;
    }
  return RC::SUCCESS;
}
