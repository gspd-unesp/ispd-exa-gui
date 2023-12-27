#include "context/context.h"
#include <qdialog.h>

class AddWorkloadWindow : public QDialog
{
public:
    AddWorkloadWindow(Context::MainContext *context, QWidget *parent);

private:
    void                   getMasters();
    Context::MainContext  *context;
    QList<QString> masters;
};
