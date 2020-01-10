SRC_URI += "file://user_2019-08-06-18-09-00.cfg \
            file://user_2019-08-07-09-56-00.cfg \
            file://user_2019-11-29-14-39-00.cfg \
            file://user_2019-11-19-15-09-00.cfg \
            "

SRC_URI += "file://0001-led-Include-Digilent-prl-PWM-RGB-LED.patch"
SRC_URI += "file://0001-staging-add-xilinx-axi-dma.patch \
        file://0002-xlnx_axidma-correct-Makefile.patch \
        file://0003-xlnx_axidma-import-updates.patch \
        file://0004-xlnx-axidma-do-not-expose-dma_addr.patch \
	    "
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

