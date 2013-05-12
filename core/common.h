#ifndef COMMON_H
#define COMMON_H

#include <QtCore/QtGlobal>

#if defined GROUP8_CORE_LIBRARY
#   define GROUP8_CORE Q_DECL_EXPORT
#else
#   define GROUP8_CORE Q_DECL_IMPORT
#endif

#endif // COMMON_H
