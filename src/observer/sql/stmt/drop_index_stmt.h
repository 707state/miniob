#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
class Db;
struct DropIndexSqlNode;
class Table;
class FieldMeta;
class DropIndexStmt:public Stmt{
  public:
    DropIndexStmt(Table *table,const FieldMeta *field_meta,const std::string &index_name):
      table_(table),index_name_(index_name),field_meta_(field_meta){}
    virtual ~DropIndexStmt()=default;
    StmtType type() const override{
      return StmtType::DROP_INDEX; 
    }
    Table *table() const{ return table_;}
    const std::string &index_name()const{return index_name_;}
	const FieldMeta *field_meta()const{
		return field_meta_;
	}
    static RC create(Db *db,const DropIndexSqlNode &drop_index,Stmt *&stmt);
  private:
    Table *table_=nullptr;
    std::string index_name_;
	const FieldMeta *field_meta_=nullptr;
};
