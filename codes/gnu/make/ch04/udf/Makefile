define parent
	echo "parent has two parameters: $1, $2."
	$(call child,$1)
endef

define child
	echo "child has one parameter: $1."
	echo "parent's second parameter is: $2."
endef

all:
	@$(call parent,one,two)
