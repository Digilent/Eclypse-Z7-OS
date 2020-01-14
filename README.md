# Eclypse Z7 Zmod DAC 1411 Petalinux Project

## Description

This is a branch of the Eclypse Z7 board containing the Petalinux project with the Zmod DAC 1411 set in Zmod connector B. Data transfers are facilitated trough the AXI DMA IP provided by Xilinx and with the kernel driver and API from [xilinx_axidma](https://github.com/bperez77/xilinx_axidma) which has been modified using patches inside the Petalinux project. This project is currently configured to boot into an INITRAMFS by default which is generated within the project; this however has limited rootfs capabilities. We have provided a ready to use image with a uEnv.txt document which allows the user to switch between hardware / kernel configurations and a Debian 10 rootfs for armv7, found here:~~[SD card image](https://reference.digilentinc.com/vivado/installing-vivado/start)~~

The hardware platform used for this Petalinux project has been imported from the [Hardware repository](https://github.com/Digilent/Eclypse-Z7-HW/tree/zmod_dac/master) of the same branch as this. In order to minimize confusion, currently the commit message of the imported hardware platform contains the commit hash of the exported hardware platform of the aforementioned Hardware repository.

## First and Foremost

* The Petalinux projects are version-specific. Source files may not be backward compatible and are not automatically forward compatible. Release tags specify the targeted Petalinux version. There is only one version targeted per year, as chosen by Digilent. Non-tagged commits on the master branch are either at the last tagged version or the next targeted version. This is not ideal and might be changed in the future adopting a better flow.

## Requirements

* **Eclypse Z7**
* **Zmod DAC 1411**
* **Petalinux 2019.1**: For installation, please follow the user guide provided by Xilinx [Petalinux Reference Guide (UG1144)](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1144-petalinux-tools-reference-guide.pdf).

## Setup

This guide will walk you through some basic steps to boot into Linux and rebuild the Petalinux project. After completing it, you should refer to the [Petalinux Reference Guide (UG1144)](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1144-petalinux-tools-reference-guide.pdf) from Xilinx to learn how to do more useful things with the Petalinux toolset. It also assumes that you have managed to install Petalinux 2019.1 as per the Xilinx user guide.

### Source the Petalinux Tools

Whenever you want to run any petalinux commands, you will need to first open a new terminal and "source" the Petalinux environment settings:

```
source /opt/pkg/petalinux/settings.sh
```

### Download the Petalinux Project

It is recommended to version control your project and rebuild it with the latest features. In order to do that, clone your repository on the appropriate branch:
```
git clone -b zmod_dac/master --single-branch https://github.com/Digilent/Eclypse-Z7-OS
```

### Build the Petalinux Project

Run the following commands to build the Petalinux project with the default options:

```
petalinux-build
petalinux-package --boot --force --fsbl images/linux/zynq_fsbl.elf --u-boot
```

### Boot the Newly Built Files from SD

Once the build is done, there are two methods to boot the newly built image.
The first assumes that you are using our prepared ~~[image with Debian 10 rootfs]()~~, in this case you only need to replace the files in the **boot partition** of the SD card with the files located in *\<repo-location\>/images/linux/*.

Alternatively, if you wish to use the the INITRAMFS you will need to first run this command:
```
petalinux-package --boot --force --fsbl images/linux/zynq_fsbl.elf --fpga images/linux/system_wrapper.bit --u-boot
```
followed by loading the *\<repo-location\>/images/linux/BOOT.bin* and *\<repo-location\>/images/linux/image.ub* to the **boot partition** of the SD card.

## Next Steps

In order to customize the Petalinux project, please refer to the [Petalinux Reference Guide (UG1144)](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1144-petalinux-tools-reference-guide.pdf) which provides all the details regarding the commands which can be used and how to use them in order to achieve this. After each customization, you will have to rebuild the project using the commands provided by the **Build the Petalinux Project** section of this document.

If you have changed the base hardware of the Vivado design referenced by this project and/or wish to import a new hardware design into this project to build upon, you will need to run:
```
petalinux-config --get-hw-description=<location-of-your-hdf>
```

**!!!IMPORTANT!!!**

Some changes to the hardware will require changes to the device-tree in *\<repo-location\>/project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi*

## Additional Notes

For information related to Petalinux, please visit [Petalinux Reference Guide (UG1144)](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2019_1/ug1144-petalinux-tools-reference-guide.pdf)

For more information on the Eclypse Z7, visit it's [Eclypse Z7 Resource Center](https://reference.digilentinc.com/reference/programmable-logic/eclypse-z7/start) on the Digilent Wiki.

For more information on the Zmod DAC 1411, please visit it's [Zmod DAC Resource Center](https://reference.digilentinc.com/reference/zmod/zmoddac/start) on the Digilent Wiki.

For more information on how our git and project flow is set up, please refer to [Eclypse Z7 Git Repositoies](https://reference.digilentinc.com/reference/programmable-logic/eclypse-z7/git).

For technical support or questions, please post on the [Digilent Forum](forum.digilentinc.com).
