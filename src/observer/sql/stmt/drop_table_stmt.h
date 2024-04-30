#pragma once

#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "sql/parser/parse_defs.h"
class Db;

class DropTableStmt:public Stmt{
  private:
    std::string relation_name_;
  public:
  DropTableStmt(const std::string& table_name)
  :relation_name_(table_name){}
  virtual ~DropTableStmt()=default;
  StmtType type() const override{
    return StmtType::DROP_TABLE;
  }    
  const std::string &table_name()const{
    return relation_name_;
  }
  static RC create(Db *db,const DropTableSqlNode& drop_table,Stmt *&stmt);
};
