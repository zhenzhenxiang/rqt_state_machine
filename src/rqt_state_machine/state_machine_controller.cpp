#include "rqt_state_machine/state_machine_controller.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <QMessageBox>

namespace rqt_state_machine {

StateMachineController::StateMachineController()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("StateMachineController");
}

void StateMachineController::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);

  connect(ui_.startFreespace, SIGNAL(clicked()), this, SLOT(onFreespaceStart()));
  connect(ui_.stopFreespace, SIGNAL(clicked()), this, SLOT(onFreespaceStop()));
}

void StateMachineController::shutdownPlugin()
{
  // TODO unregister all publishers here
}

void StateMachineController::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void StateMachineController::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}

// freespace state control functions
void StateMachineController::onFreespaceStart()
{
  freespace_ros::FreespaceControl srv;
  srv.request.action.module = 1;
  srv.request.action.command = 1;

  if (ros::service::call("freespace_state_control", srv))
  {
    QMessageBox::information(widget_, "start", "Succeed to start freespace!");
  }
  else
  {
    QMessageBox::warning(widget_, "start", "Failed to start freespace!");
    return;
  }
}

void StateMachineController::onFreespaceStop()
{
  freespace_ros::FreespaceControl srv;
  srv.request.action.module = 1;
  srv.request.action.command = 0;

  if (ros::service::call("freespace_state_control", srv))
  {
    QMessageBox::information(widget_, "stop", "Succeed to stop freespace!");
  }
  else
  {
    QMessageBox::warning(widget_, "stop", "Failed to stop freespace!");
    return;
  }
}

/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

} // namespace
PLUGINLIB_DECLARE_CLASS(rqt_state_machine, StateMachineController, rqt_state_machine::StateMachineController, rqt_gui_cpp::Plugin)
