##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CACC
ConfigurationName      :=Debug
WorkspacePath          := "/Users/csacanam/Documents/Desarrollos/CodeLiteWorkspace"
ProjectPath            := "/Users/csacanam/Documents/Desarrollos/CodeLiteWorkspace/CACC"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Juan Camilo Sacanamboy
Date                   :=2015-04-13
CodeLitePath           :="/Users/csacanam/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="CACC.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/Users/csacanam/Downloads/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/CustomAppLayer.cc$(ObjectSuffix) $(IntermediateDirectory)/NodeInfo.cc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Users/csacanam/Documents/Desarrollos/CodeLiteWorkspace/CACC/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/CustomAppLayer.cc$(ObjectSuffix): CustomAppLayer.cc $(IntermediateDirectory)/CustomAppLayer.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/csacanam/Documents/Desarrollos/CodeLiteWorkspace/CACC/CustomAppLayer.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CustomAppLayer.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CustomAppLayer.cc$(DependSuffix): CustomAppLayer.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CustomAppLayer.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/CustomAppLayer.cc$(DependSuffix) -MM "CustomAppLayer.cc"

$(IntermediateDirectory)/CustomAppLayer.cc$(PreprocessSuffix): CustomAppLayer.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CustomAppLayer.cc$(PreprocessSuffix) "CustomAppLayer.cc"

$(IntermediateDirectory)/NodeInfo.cc$(ObjectSuffix): NodeInfo.cc $(IntermediateDirectory)/NodeInfo.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/csacanam/Documents/Desarrollos/CodeLiteWorkspace/CACC/NodeInfo.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NodeInfo.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NodeInfo.cc$(DependSuffix): NodeInfo.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NodeInfo.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/NodeInfo.cc$(DependSuffix) -MM "NodeInfo.cc"

$(IntermediateDirectory)/NodeInfo.cc$(PreprocessSuffix): NodeInfo.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NodeInfo.cc$(PreprocessSuffix) "NodeInfo.cc"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


