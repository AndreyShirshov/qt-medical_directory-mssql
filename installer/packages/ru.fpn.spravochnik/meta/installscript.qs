function Component()
{
    installer.installationFinished.connect(this, Component.prototype.finishedPageShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/Spravochnik.exe", "@StartMenuDir@/Справочник.lnk", "workingDirectory=@TargetDir@");
        component.addOperation("CreateShortcut", "@TargetDir@/InstallTools.exe", "@StartMenuDir@/InstallTools.lnk", "workingDirectory=@TargetDir@");
        component.addOperation("CreateShortcut", "@TargetDir@/README.txt", "@StartMenuDir@/README.lnk","workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll", "iconId=2", "description=Open README file");
        component.addOperation("CreateShortcut", "@TargetDir@/Spravochnik.exe", "@DesktopDir@/Справочник.lnk", "workingDirectory=@TargetDir@", "description=Start Application");
    }
}

Component.prototype.finishedPageShown= function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
			installer.addWizardPageItem( component, "ReadMeCheckBoxForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        print(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            if (component.userInterface("ReadMeCheckBoxForm" ).readMeCheckBox.checked)
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/README.txt");
        }
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            if (component.userInterface("ReadMeCheckBoxForm" ).runMeCheckBox.checked)
				QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/Spravochnik.exe");
        }
    } catch(e) {
        print(e);
    }
}
