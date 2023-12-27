#include "window/addworkloadwindow.h"
#include "components/schema.h"
#include "components/conf/machineconfiguration.h"
#include "context/context.h"
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qgridlayout.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qspinbox.h>

AddWorkloadWindow::AddWorkloadWindow(Context::MainContext *context, QWidget *parent)
    : QDialog(parent), context{context}
{
    auto ownerLabel = new QLabel("Owner");
    auto masterLabel = new QLabel("Master");
    auto processingLabel = new QLabel("Processing");
    auto communicationLabel = new QLabel("Communication");
    auto tasksLabel = new QLabel("Tasks");
    auto arrivalLabel = new QLabel("Arrival");
    auto typeLabel = new QLabel("type");
    auto lambdaLabel = new QLabel("Lambda");
    auto minLabel = new QLabel("min");
    auto maxLabel = new QLabel("max");

    //
    // OwnerLabel OwnerComboBox MasterLabel MasterComboBox
    //
    // CommunicationLabel MinLabel MinCommEditLine MaxLabel MaxCommEditLine
    // ProcessingLabel MinLabel MinProcessEditLine MaxLabel MaxProcessEditLine
    // TasksLabel tasksEditLine
    // ArrivalLabel TypeLabel TypeComboBox LambdaLabel LambdaEditLine
    //
    auto masterComboBox = new QComboBox();
    this->getMasters();
    masterComboBox->addItems(this->masters);

    auto configLayout = new QGridLayout();
    configLayout->addWidget(ownerLabel, 0, 1);
    configLayout->addWidget(new QComboBox(), 0, 2);
    configLayout->addWidget(masterLabel, 0, 3);
    configLayout->addWidget(masterComboBox, 0, 4);

    configLayout->addWidget(communicationLabel, 1, 0);
    configLayout->addWidget(new QLabel("min"), 1, 1);
    configLayout->addWidget(new QSpinBox(), 1, 2);
    configLayout->addWidget(new QLabel("max"), 1, 3);
    configLayout->addWidget(new QSpinBox(), 1, 4);

    configLayout->addWidget(processingLabel, 2, 0);
    configLayout->addWidget(new QLabel("min"), 2, 1);
    configLayout->addWidget(new QSpinBox(), 2, 2);
    configLayout->addWidget(new QLabel("max"), 2, 3);
    configLayout->addWidget(new QSpinBox(), 2, 4);

    configLayout->addWidget(tasksLabel, 3, 1);
    configLayout->addWidget(new QSpinBox(), 3, 2);

    configLayout->addWidget(arrivalLabel, 4, 0);
    configLayout->addWidget(typeLabel, 4, 1);
    configLayout->addWidget(new QComboBox(), 4, 2);
    configLayout->addWidget(lambdaLabel, 4, 3);
    configLayout->addWidget(new QComboBox(), 4, 4);

    auto configFrame = new QFrame(this);
    configFrame->setLayout(configLayout);
    auto mainLayout = new QVBoxLayout(this);

    //-------------------------------------------------------------------------

    auto buttonFrame = new QFrame(this);
    auto buttonLayout = new QHBoxLayout(buttonFrame);
    buttonLayout->setAlignment(Qt::AlignRight);

    auto okButton = new QPushButton("Ok");
    auto cancelButton = new QPushButton("Cancel");

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);


    //-------------------------------------------------------------------------

      // Create a horizontal line as a separator
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // Set the frame shape to a horizontal line
    line->setFrameShadow(QFrame::Sunken); // Optional: give the line a shadow effect

    mainLayout->addWidget(configFrame);
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonFrame);

    this->setFixedSize(mainLayout->sizeHint());

    this->setWindowTitle("Add Workload");
}

void AddWorkloadWindow::getMasters() {
    auto connectables = &context->mainSchema->connectables;

    for (auto const &[i, connectable] : *connectables) {
        if (auto const machine = dynamic_cast<Machine *>(connectable.get()); machine != nullptr) {
            if (static_cast<MachineConfiguration *>(machine->getConf())->master) {
                masters.push_back(QString::fromStdString(machine->getConf()->getName()));
            }
        }
    }

    // TODO add recursion for further schemas
}
