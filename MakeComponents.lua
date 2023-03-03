TemplateHeader = [[
// This is a generated file, do not edit manually

#ifndef _KGE_COMPONENTS_H
#define _KGE_COMPONENTS_H

#include "klm.h"

]]

TemplateStruct = [[
typedef struct $NAME$ {
$MEMBER_VALUES$} $NAME$;
#define GET_COMPONENT_VALUE_$NAME$ COMPONENT_$UPPERNAME$
#define GET_COMPONENT_SIZE_COMPONENT_$INDEX$ sizeof($NAME$)
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_$UPPERNAME$ sizeof($NAME$)

]]

TemplateEnumStart = [[
// Master list of components.
enum COMPONENT_ENUM {
	COMPONENT_NONE,
]]

TemplateFooter = [[
};
typedef enum COMPONENT_ENUM COMPONENT_ENUM;

#define GET_COMPONENT_SIZE_COMPONENT_0 0
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_NONE 0
#define cp_type(comp) ((size_t)GET_COMPONENT_VALUE_##comp)
#define cp_size(enm) GET_COMPONENT_SIZE_COMPONENT_##enm

#endif // _KGE_COMPONENTS_H
]]

local function readSourceFile(targetFile, sourceFile)
	local source = io.open(sourceFile, 'r')
	local line = source:read'l'
	while line do
		local s, _, name = line:find("^([_%a][_%w]*):$")
		if s then
			table.insert(CList, name:upper())
			line = source:read"l"
			local members = ""
			while line and line:find("^\t") do
				members = members .. line .. ";\n"
				line = source:read'l'
			end

			local struct = TemplateStruct:gsub("%$NAME%$", name)
			struct = struct:gsub("%$UPPERNAME%$", name:upper())
			struct = struct:gsub("%$MEMBER_VALUES%$", members)
			struct = struct:gsub("%$INDEX%$", #CList)
			targetFile:write(struct)
		else
			line = source:read"l"
		end
	end
	source:close()
end

CList = {}
local targetFile = io.open("src/Components.h", "w+")
targetFile:write(TemplateHeader)

local fileList = io.popen("ls src/Components | grep .csp$", "r")
for f in fileList:lines"l" do
	print(f)
	readSourceFile(targetFile, "src/Components/" .. f)
end
fileList:close()

targetFile:write(TemplateEnumStart)

for i=1, #CList do
	targetFile:write("\tCOMPONENT_" .. CList[i] .. ",\n")
end

targetFile:write(TemplateFooter)
targetFile:close()

