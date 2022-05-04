#ifndef LOGICLIB_GLOBAL_H
#define LOGICLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGICLIB_LIBRARY)
#  define LOGICLIB_EXPORT Q_DECL_EXPORT
#else
#  define LOGICLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGICLIB_GLOBAL_H
