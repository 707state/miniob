#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include <vector>
class AlterColumnModifyStmt:public Stmt{
  private:
    std::string relation_name_;
    std::vector<AttrInfoSqlNode> attr_infos_;
  public:
    AlterColumnModifyStmt(const std::string& table_name,const std::vector<AttrInfoSqlNode>& attr_infos):
    relation_name_(table_name),attr_infos_(attr_infos){}
    StmtType type()const{
      return StmtType::ALTER_COLUMN_MODIFY;
    }
    const std::string& table_name()const{
      return relation_name_;
    }
    const std::vector<AttrInfoSqlNode>& attr_infos()const{
      return attr_infos_;
    }
    static RC create(Db *db,const AlterColumnModifySqlNode& alter_column_modify,Stmt *&stmt);
};
