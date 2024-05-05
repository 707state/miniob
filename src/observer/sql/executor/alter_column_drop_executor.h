#include "event/sql_event.h"
class AlterColumnDropExecutor{
  public:
    AlterColumnDropExecutor()=default;
    ~AlterColumnDropExecutor()=default;
    RC execute(SQLStageEvent *sql_event);
};
