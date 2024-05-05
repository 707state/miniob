#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
class AlterColumnDropStmt:public Stmt{
  private:
    std::string relation_name_;
    std::string attribute_name_;
  public:
    AlterColumnDropStmt(const std::string& table_name,const std::string& attribute_name):
    relation_name_(table_name),attribute_name_(attribute_name){}
    virtual ~AlterColumnDropStmt(){}
    StmtType type()const{
      return StmtType::ALTER_COLUMN_DROP;
    }  
    const std::string& table_name()const{
      return relation_name_;
    }
    const std::string& attribute_name()const{
      return attribute_name_;
    }
    static RC create(Db *db,const AlterColumnDropSqlNode& alter_column_drop,Stmt *&stmt);
};
