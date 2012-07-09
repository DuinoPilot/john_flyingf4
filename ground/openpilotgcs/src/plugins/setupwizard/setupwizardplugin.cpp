/**
 ******************************************************************************
 *
 * @file       donothingplugin.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup SetupWizardPlugin Do Nothing Plugin
 * @{
 * @brief A Setup Wizard Plugin
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include "setupwizardplugin.h"

#include <QDebug>
#include <QtPlugin>
#include <QStringList>
#include <extensionsystem/pluginmanager.h>

#include <coreplugin/coreconstants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/icore.h>
#include <QKeySequence>

SetupWizardPlugin::SetupWizardPlugin()
{
   // Do nothing
}

SetupWizardPlugin::~SetupWizardPlugin()
{
}

bool SetupWizardPlugin::initialize(const QStringList& args, QString *errMsg)
{
    Q_UNUSED(args);
    Q_UNUSED(errMsg);

    // Add Menu entry
    Core::ActionManager* am = Core::ICore::instance()->actionManager();
    Core::ActionContainer* ac = am->actionContainer(Core::Constants::M_TOOLS);

    Core::Command* cmd = am->registerAction(new QAction(this),
                                            "SetupWizardPlugin.ShowSetupWizard",
                                            QList<int>() <<
                                            Core::Constants::C_GLOBAL_ID);
    cmd->setDefaultKeySequence(QKeySequence("Ctrl+W"));
    cmd->action()->setText(tr("GCS Setup Wizard"));

    ac->menu()->addSeparator();
    ac->appendGroup("Wizard");
    ac->addAction(cmd, "Wizard");

    connect(cmd->action(), SIGNAL(triggered(bool)), this, SLOT(showSetupWizard()));
    return true;
}

void SetupWizardPlugin::extensionsInitialized()
{
}

void SetupWizardPlugin::shutdown()
{
}

void SetupWizardPlugin::showSetupWizard()
{
    SetupWizard().exec();
}

Q_EXPORT_PLUGIN(SetupWizardPlugin)
