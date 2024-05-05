#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_index_stmt.h"
#include "sql/stmt/drop_index_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <memory>
class AlterTableModifyStmt:public Stmt{
  private:
    Table *table_=nullptr;
    const FieldMeta *field_meta_=nullptr;
    std::string relation_name_;
    std::string index_name_;
    std::string attribute_name_;
  public:
    AlterTableModifyStmt(Table *table,const FieldMeta *field_meta,const std::string &relation_name,const std::string index_name,\
    const std::string &attribute_name):
    table_(table),field_meta_(field_meta),
      relation_name_(relation_name),index_name_(index_name),attribute_name_(attribute_name){}
    virtual ~AlterTableModifyStmt()=default;
    StmtType type() const{
      return StmtType::ALTER_INDEX_MODIFY;
    }
    Table *table()const{
      return table_;
    }
    const FieldMeta *field_meta()const{
      return field_meta_;
    }
     const std::string& table_name()const{
      return relation_name_;
    }
    const std::string& index_name() const{
      return index_name_;
    }
    const std::string& attribute_name() const{
      return attribute_name_;
    }
    // std::unique_ptr<CreateIndexStmt> &add_index(){
    //   return add_index_;
    // }
    // std::unique_ptr<DropIndexStmt> &drop_index(){
    //   return drop_index_;
    // }
    static RC create(Db *db,const AlterIndexModifySqlNode &modify_index,Stmt *&stmt);
};
