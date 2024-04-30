#pragma once
#include "sql/parser/parse_defs.h"
#include "sql/stmt/drop_index_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <memory>
#include <mutex>
#include <string>
class Db;
class AlterTableDropStmt:public Stmt{
  private:
    std::string relation_name_;
    std::string index_name_;
    Table *table_;
    const FieldMeta *field_meta_;    
  public:
    AlterTableDropStmt(const std::string& relation_name,const std::string &index_name):
    relation_name_(relation_name),index_name_(index_name){}
    AlterTableDropStmt(Table *table,const FieldMeta *field_meta,const std::string &index_name):
    index_name_(index_name),table_(table),field_meta_(field_meta){}
    virtual~ AlterTableDropStmt()=default;
    StmtType type()const {
      return StmtType::ALTER_TABLE_DROP;
    }
    const std::string& table_name()const{
      return relation_name_;
    }
    const std::string& index_name()const{
      return index_name_;
    }
    Table *table()const{
      return table_;
    }
    const FieldMeta *field_meta()const{
      return field_meta_;
    }
    // auto drop_index(){
    //   return drop_index_;
    // }
    static RC create(Db *db,const AlterDropSqlNode &alter_table_drop,Stmt *&stmt);
};
