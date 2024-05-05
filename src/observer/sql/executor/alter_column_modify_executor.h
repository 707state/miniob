#include "common/rc.h"
#include "event/sql_event.h"
class AlterColumnModifyExecutor{
  public:
    AlterColumnModifyExecutor()=default;
    ~AlterColumnModifyExecutor()=default;
    RC execute(SQLStageEvent *sql_event);
};
