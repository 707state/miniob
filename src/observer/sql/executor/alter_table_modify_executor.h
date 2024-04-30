#pragma once
#include "event/sql_event.h"
class SQLStageEvent;
class AlterTableModifyExecutor
{

public:
  AlterTableModifyExecutor()          = default;
  virtual ~AlterTableModifyExecutor() = default;
  RC execute(SQLStageEvent *sql_event);
};
