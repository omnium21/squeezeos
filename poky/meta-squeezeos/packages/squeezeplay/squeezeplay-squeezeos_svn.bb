DESCRIPTION = "SqueezePlay - SqueezeOS specific code"
LICENSE = "Logitech Public Source License"

PV = "${DISTRO_VERSION}+svnr${SRCREV}"
PR = "r2"

DEPENDS += "squeezeplay"

SRC_URI="${SQUEEZEPLAY_SCM};module=squeezeplay_squeezeos"

S = "${WORKDIR}/squeezeplay_squeezeos"

inherit autotools

CFLAGS_prepend = '-DSQUEEZEPLAY_RELEASE=\\"${DISTRO_VERSION}\\" -DSQUEEZEPLAY_REVISION=\\"${SQUEEZEOS_REVISION}\\"'

CFLAGS += -I${STAGING_INCDIR}/glib-2.0 -I${STAGING_INCDIR}/../lib/glib-2.0/include -I${STAGING_INCDIR}/pango-1.0 -I${STAGING_INCDIR}/freetype2 -I${STAGING_INCDIR}/cairo

EXTRA_OEMAKE = "all lua-lint"


do_install() {
	autotools_do_install

	# move lua libraries to correct location
	rm ${D}${libdir}/* 
	mkdir -p ${D}${libdir}/lua/5.1
	install -m 0755 .libs/jiveWireless.so ${D}${libdir}/lua/5.1/jiveWireless.so
	install -m 0755 .libs/jiveWatchdog.so ${D}${libdir}/lua/5.1/jiveWatchdog.so
}


FILES_${PN} += "${datadir} ${libdir}/lua/5.1"
FILES_${PN}-dbg += "${libdir}/lua/5.1/.debug"
