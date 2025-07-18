// This C program includes the generated header (instructions.h), reads the instruction data, and emits it in YAML format using libcyaml// 
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h" // Default header, can be overridden by Makefile

/* CYAML schema for the 'variable_field_t' struct */
static const cyaml_schema_field_t field_schema_fields[] = {
    CYAML_FIELD_STRING_PTR("name", CYAML_FLAG_POINTER, variable_field_t, name, 0, CYAML_UNLIMITED),
    CYAML_FIELD_INT("width", CYAML_FLAG_DEFAULT, variable_field_t, width),
    CYAML_schema_field_t_end
};

/* CYAML schema for the 'instruction_t' struct */
static const cyaml_schema_field_t instruction_schema_fields[] = {
    CYAML_FIELD_STRING_PTR("description", CYAML_FLAG_POINTER, instruction_t, description, 0, CYAML_UNLIMITED),
    CYAML_FIELD_STRING_PTR("isa", CYAML_FLAG_POINTER, instruction_t, isa, 0, CYAML_UNLIMITED),
    CYAML_FIELD_STRING_PTR("format", CYAML_FLAG_POINTER, instruction_t, format, 0, CYAML_UNLIMITED),
    CYAML_FIELD_STRING_PTR("opcode", CYAML_FLAG_POINTER, instruction_t, opcode, 0, CYAML_UNLIMITED),
    CYAML_FIELD_SEQUENCE("variable_fields", CYAML_FLAG_POINTER, instruction_t, variable_fields, num_variable_fields, field_schema_fields, 0, CYAML_UNLIMITED),
    CYAML_schema_field_t_end
};

/* CYAML schema for a mapping of instruction names to instruction data */
static const cyaml_schema_value_t instruction_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_DEFAULT,
            instruction_t, instruction_schema_fields),
};

/* Top-level CYAML schema for a mapping where keys are instruction names */
static const cyaml_schema_field_t top_level_schema_fields[] = {
    CYAML_MAPPING_ENTRIES_FROM_ARRAY_OF_POINTERS(all_instructions, instruction_schema),
    CYAML_schema_field_t_end
};

static const cyaml_schema_value_t top_level_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_DEFAULT,
            cyaml_empty_string_t, top_level_schema_fields),
};

/* CYAML configuration */
static const cyaml_config_t config = {
    .log_level = CYAML_LOG_WARNING,
    .log_fn = cyaml_log,
    .mem_fn = cyaml_mem,
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output.yml>\n", argv[0]);
        return 1;
    }

    const char *output_path = argv[1];
    cyaml_err_t err;

    /* Create a dummy root data structure for CYAML to operate on */
    cyaml_empty_string_t root_data = "";

    /* Save the data to a YAML file */
    err = cyaml_save_file(output_path, &config, &top_level_schema, &root_data, 0);
    if (err != CYAML_OK) {
        fprintf(stderr, "ERROR: %s\n", cyaml_strerror(err));
        return 1;
    }

    printf("Successfully wrote YAML to %s\n", output_path);

    return 0;
}
