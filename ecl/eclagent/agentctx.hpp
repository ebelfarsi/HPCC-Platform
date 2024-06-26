/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */
#ifndef AGENTCTX_HPP_INCL
#define AGENTCTX_HPP_INCL

#include "errorlist.h"
#include "dautils.hpp"
#include "eclhelper.hpp"
#include "rtldynfield.hpp"
#include "workunit.hpp"

#if (ECLAGENT_ERROR_START != 5400 || ECLAGENT_ERROR_END != 5499)
#error "ECLAGENT_ERROR_START has changed"
#endif

#define WRN_SkipMissingOptIndex             5400
#define WRN_SkipMissingOptFile              5401
#define WRN_UseLayoutTranslation            5402
#define WRN_UnsupportedAlgorithm            5403
#define WRN_MismatchGroupInfo               5404
#define WRN_MismatchCompressInfo            5405
#define WRN_RemoteReadFailure               5406

class EclGraph;
struct IHThorGraphResult : extends IInterface
{
    virtual void addRowOwn(const void * row) = 0;
    virtual const void * queryRow(unsigned whichRow) = 0;
    virtual void getLinkedResult(unsigned & count, const byte * * & ret) = 0;
    virtual const void * getOwnRow(unsigned whichRow) = 0;      // used internally, removes row from result
    virtual const void * getLinkedRowResult() = 0;
};

struct ILocalEclGraphResults : public IEclGraphResults
{
public:
    virtual IHThorGraphResult * queryResult(unsigned id) = 0;
    virtual IHThorGraphResult * queryGraphLoopResult(unsigned id) = 0;
    virtual IHThorGraphResult * createResult(unsigned id, IEngineRowAllocator * ownedRowsetAllocator) = 0;
    virtual IHThorGraphResult * createGraphLoopResult(IEngineRowAllocator * ownedRowsetAllocator) = 0;
};

struct IHThorGraphResults : extends ILocalEclGraphResults
{
    virtual void clear() = 0;
    virtual IHThorGraphResult * queryResult(unsigned id) = 0;
    virtual IHThorGraphResult * createResult(unsigned id, IEngineRowAllocator * ownedRowsetAllocator) = 0;
    virtual IHThorGraphResult * createResult(IEngineRowAllocator * ownedRowsetAllocator) = 0;
    virtual void setResult(unsigned id, IHThorGraphResult * result) = 0;
    virtual int ordinality() = 0;
};

struct IHThorBoundLoopGraph : extends IInterface
{
    virtual IHThorGraphResults * execute(void * counterRow, ConstPointerArray & rows, const byte * parentExtract) = 0;
    virtual void execute(void * counterRow, IHThorGraphResults * graphLoopResults, const byte * parentExtract) = 0;
};

struct IEclLoopGraph : public IInterface
{
    virtual void executeChild(const byte * parentExtract, IHThorGraphResults * results, IHThorGraphResults * _graphLoopResults) = 0;
};

interface IOrderedOutputSerializer;

typedef enum { ofSTD, ofXML, ofRAW } outputFmts;
enum class AccessMode : unsigned;

struct IAgentContext : extends IGlobalCodeContext
{
    virtual void reportProgress(const char *msg, unsigned flags=0) = 0;
    virtual bool queryResolveFilesLocally() = 0;
    virtual bool queryRemoteWorkunit() = 0;
    virtual bool queryWriteResultsToStdout() = 0;
    virtual outputFmts queryOutputFmt() = 0;

    virtual ICodeContext *queryCodeContext() = 0;

    virtual IConstWorkUnit *queryWorkUnit() const = 0;
    virtual IWorkUnit *updateWorkUnit() const = 0;
    
    virtual ILocalOrDistributedFile *resolveLFN(const char *logicalName, const char *errorTxt, bool optional, bool noteRead, AccessMode accessMode, StringBuffer * expandedlfn, bool isPrivilegedUser) = 0;
    virtual StringBuffer & getTempfileBase(StringBuffer & buff) = 0;
    virtual const char *noteTemporaryFile(const char *fname) = 0;
    virtual const char *noteTemporaryFilespec(const char *fname) = 0;
    virtual const char *queryTemporaryFile(const char *fname) = 0;
    virtual void reloadWorkUnit() = 0;

    virtual char *resolveName(const char *in, char *out, unsigned outlen) = 0;
    virtual void logFileAccess(IDistributedFile * file, char const * component, char const * type, EclGraph & graph) = 0;
    virtual void addWuException(const char * text, unsigned code, unsigned severity, char const * source) = 0;

    virtual IHThorGraphResults * executeLibraryGraph(const char * libraryName, unsigned expectedInterfaceHash, unsigned activityId, const char * embeddedGraphName, const byte * parentExtract) = 0;
    virtual bool getWorkunitResultFilename(StringBuffer & diskFilename, const char * wuid, const char * name, int seq) = 0;
    virtual IHThorGraphResults * createGraphLoopResults() = 0;
    virtual void outputFormattedResult(const char *name, unsigned sequence, bool close) = 0;

    virtual const char *queryAllowedPipePrograms() = 0;
    
    virtual IOrderedOutputSerializer * queryOutputSerializer() = 0;

    virtual IGroup *getHThorGroup(StringBuffer &grpnameout) = 0;

    virtual RecordTranslationMode getLayoutTranslationMode() const = 0;
    virtual unsigned __int64 queryStopAfter() = 0;
    
    virtual const char *queryWuid() = 0;

    virtual void updateWULogfile(IWorkUnit *outputWU) = 0;
    virtual bool forceNewDiskReadActivity() const = 0;
    virtual void addWuExceptionEx(const char * text, unsigned code, unsigned severity, unsigned audience, char const * source) = 0;
    virtual double queryAgentMachineCost() const = 0;
    virtual void updateAggregates(IWorkUnit* lockedwu) = 0;
    virtual void mergeAggregatorStats(IStatisticCollection & stats, unsigned wfid, const char *graphname, unsigned sgId) = 0;
};

#endif // AGENTCTX_HPP_INCL
