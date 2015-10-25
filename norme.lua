for i,v in pairs(arg) do
	local modified = v:gsub("(%.%S*)", "_adebray_03%1")

	os.execute('cp '..v..' '..modified)
	os.execute('norminette '..modified)
end
