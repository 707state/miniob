#pragma once
#include "common/rc.h"
#include "event/sql_event.h"
#include "sql/executor/alter_table_add_executor.h"
class SQLStageEvent;

class AlterTableDropExecuter
{
public:
  AlterTableDropExecuter()          = default;
  virtual ~AlterTableDropExecuter() = default;
  RC execute(SQLStageEvent *sql_event);
};
