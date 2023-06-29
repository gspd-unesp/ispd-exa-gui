#include "drawingtable/scene.h"
#include "drawingtable/view.h"
#include <QMainWindow>

class ClusterWindow : QMainWindow
{
    Q_OBJECT

public:
    ClusterWindow(QWidget *parent = nullptr);

private:
    Scene *scene;
    View  *view;
};
