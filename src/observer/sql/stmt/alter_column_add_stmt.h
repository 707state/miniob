#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
class AlterColumnAddStmt:public Stmt{
  private:
    std::string relation_name_;
    std::vector<AttrInfoSqlNode> attr_infos_;
  public:
    AlterColumnAddStmt(const std::string& table_name_,const std::vector<AttrInfoSqlNode>& attr_infos):
    relation_name_(table_name_),attr_infos_(attr_infos){}
    virtual ~AlterColumnAddStmt(){};
    StmtType type()const{
      return StmtType::ALTER_COLUMN_ADD;
    }
    const std::string& table_name()const{
      return relation_name_;
    }
    std::vector<AttrInfoSqlNode>& attr_infos(){
      return attr_infos_;
    }
    static RC create(Db *db,const AlterColumnAddSqlNode& alter_column_add,Stmt *&stmt);
};
