MACHINEOVERRIDES =. "mx93:"

require conf/machine/include/imx-base.inc
require conf/machine/include/arm/armv8-2a/tune-cortexa55.inc

MACHINE_FEATURES += "pci wifi bluetooth"
MACHINE_FEATURES:append:use-nxp-bsp = " optee jailhouse nxpiw612-sdio dpdk nxpwifi-all-sdio"

MACHINE_FIRMWARE:append:use-nxp-bsp = " ethos-u-firmware"

KERNEL_DEVICETREE = " \
    freescale/${KERNEL_DEVICETREE_BASENAME}.dtb \
"
UBOOT_DTB_NAME = "${KERNEL_DEVICETREE_BASENAME}.dtb"

IMX_DEFAULT_BOOTLOADER:use-nxp-bsp = "u-boot-imx"
IMX_DEFAULT_BOOTLOADER:use-mainline-bsp = "u-boot-fslc"

LOADADDR = ""
UBOOT_SUFFIX = "bin"
UBOOT_MAKE_TARGET = ""

SPL_BINARY = "spl/u-boot-spl.bin"

UBOOT_CONFIG ??= "sd"
UBOOT_CONFIG[sd]   = "${UBOOT_CONFIG_BASENAME}_defconfig,sdcard"
UBOOT_CONFIG[ecc]  = "${UBOOT_CONFIG_BASENAME}_inline_ecc_defconfig"
UBOOT_CONFIG[fspi] = "${UBOOT_CONFIG_BASENAME}_defconfig"

# Set ATF platform name
ATF_PLATFORM = "imx93"

IMXBOOT_TARGETS = \
    "${@bb.utils.contains('UBOOT_CONFIG',   'sd', '${IMXBOOT_TARGETS_SD}', \
        bb.utils.contains('UBOOT_CONFIG',  'ecc', '${IMXBOOT_TARGETS_ECC}', \
        bb.utils.contains('UBOOT_CONFIG', 'fspi', '${IMXBOOT_TARGETS_FSPI}', \
                                                  'INVALID', d), d), d)}"
# Note different SD targets for different Glitch Detection (GDET) modes:
# | Target                     | Glitch Detection                                 |
# | flash_singleboot           | None                                             |
# | flash_singleboot_gdet      | Enabled                                          |
# | flash_singleboot_gdet_auto | Enabled during EdgeLock Secure Enclave API calls |
IMXBOOT_TARGETS_SD   = "flash_singleboot flash_singleboot_gdet flash_singleboot_gdet_auto"
IMXBOOT_TARGETS_ECC  = "flash_singleboot"
IMXBOOT_TARGETS_FSPI = "flash_singleboot_flexspi"

IMX_BOOT_SOC_TARGET = "iMX9"
IMX_BOOT_SEEK = "32"

# We have to disable SERIAL_CONSOLE due to auto-serial-console
SERIAL_CONSOLES = "115200;ttyLP0"

IMX_DEFAULT_BSP = "nxp"
