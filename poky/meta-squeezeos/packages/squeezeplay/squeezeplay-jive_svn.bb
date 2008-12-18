DESCRIPTION = "SqueezePlay - Jive specific code"
LICENSE = "Logitech Public Source License"

PV = "${DISTRO_VERSION}+svnr${SRCREV}"
PR = "r16"

DEPENDS += "squeezeplay"

SRC_URI="${SQUEEZEPLAY_SCM};module=squeezeplay_jive"

S = "${WORKDIR}/squeezeplay_jive"

inherit autotools

CFLAGS_prepend = '-DSQUEEZEPLAY_RELEASE=\\"${DISTRO_VERSION}\\" -DSQUEEZEPLAY_REVISION=\\"${SQUEEZEOS_REVISION}\\"'

CFLAGS += -I${STAGING_INCDIR}/glib-2.0 -I${STAGING_INCDIR}/../lib/glib-2.0/include -I${STAGING_INCDIR}/pango-1.0 -I${STAGING_INCDIR}/freetype2 -I${STAGING_INCDIR}/cairo

EXTRA_OEMAKE = "all lua-lint"


do_install() {
	autotools_do_install

	# move lua libraries to correct location
	rm ${D}${libdir}/* 
	mkdir -p ${D}${libdir}/lua/5.1
	install -m 0755 .libs/jiveBSP.so ${D}${libdir}/lua/5.1/jiveBSP.so
}


FILES_${PN} += "${datadir} ${libdir}/lua/5.1"
FILES_${PN}-dbg += "${libdir}/lua/5.1/.debug"
