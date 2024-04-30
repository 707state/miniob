#pragma once
#include "common/rc.h"
#include "event/sql_event.h"
#include "sql/parser/parse_defs.h"
#include <algorithm>
#include <memory>
class SQLStageEvent;

class AlterTableAddExecuter
{
private:public:
  AlterTableAddExecuter()          = default;
  virtual ~AlterTableAddExecuter() = default;
  RC execute(SQLStageEvent *sql_event);
};
