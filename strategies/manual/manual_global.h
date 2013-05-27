#ifndef MANUAL_GLOBAL_H
#define MANUAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MANUAL_LIBRARY)
#  define MANUALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MANUALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MANUAL_GLOBAL_H
