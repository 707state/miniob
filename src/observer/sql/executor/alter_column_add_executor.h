#include "event/sql_event.h"
class AlterColumnAddExecutor{
  public:
    AlterColumnAddExecutor()=default;
    ~AlterColumnAddExecutor()=default;
    RC execute(SQLStageEvent *sql_event);
};
