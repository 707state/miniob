#pragma once
#include <memory>
#include <string>
#include <vector>

#include "sql/stmt/create_index_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
class Db;
class AlterTableAddStmt:public Stmt{
  private:
    std::string relation_name_;
    std::string index_name_;
    std::string attribute_name_;
    Table *table_=nullptr;
    const FieldMeta *field_mete_=nullptr;
   public:
    // AlterTableAddStmt(const std::string &relation_name,const std::string & index_name,const std::string& attribute_name):
    //   relation_name_(relation_name),index_name_(index_name),attribute_name_(attribute_name){
        
    //   }
    AlterTableAddStmt(Table *table,const FieldMeta *field_meta,const std::string &relation_name,
                    const std::string& index_name,const std::string& attribute_name):
   relation_name_(relation_name),index_name_(index_name ),attribute_name_(attribute_name),table_(table),field_mete_(field_meta)
    {}    
      virtual ~AlterTableAddStmt()=default;
      StmtType type()const{return StmtType::ALTER_TABLE_ADD;}
      const std::string &table_name()const{
        return relation_name_;
      }
      const std::string &index_name()const{
        return index_name_;
      }
      const std::string& attribute_name()const{
        return attribute_name_;
      }
      // std::unique_ptr<CreateIndexStmt> &add_index(){
      //   return add_index_;
      // }
      Table *table()const{
        return table_;
      }
      const FieldMeta *field_meta()const{
        return field_mete_;
      }
      static RC create(Db *db,const AlterAddSqlNode & alter_table_add,Stmt *&stmt );
};
