# Code-Gen-From-UDB-to-Implementations
# An Idempotent Data Transformation Pipeline for RISC-V ISA Specifications: From UDB YAML to C and Back:

This project demonstrates a round-trip conversion process: from a RISC-V instruction definition in YAML to a C header file, and then back to YAML. The process is designed to be idempotent, meaning the second YAML generation produces a file identical to the first.

This toolchain uses Python with the `PyYAML` library for the initial YAML-to-C conversion and a C program with the `libcyaml` library for the C-to-YAML conversion.

## 🏛️ Project Structure:
riscv-yaml-converter/
├── C/
│   ├── main.c
│   └── Makefile
├── python/
│   └── yaml_to_c.py
├── data/
│   └── rv32i.yml
└── README.md
### Prerequisites

* **Python 3**: With the `PyYAML` library.
    ```bash
    pip install PyYAML
    ```
* **C Compiler**: Such as GCC.
* **`libcyaml`**: A C library for YAML serialization and deserialization. Follow the installation instructions on the official [`libcyaml` GitHub repository](https://github.com/tlsa/libcyaml).

### 📝 Usage

## Step 1: Generate the C header from YAML

Run the Python script to read `rv32i.yml` and generate the C header file `instructions.h`.

```bash
python python/yaml_to_c.py data/rv32i.yml C/instructions.h
## Step 2:Compile the C programme 
Use the provided Makefile to build the C executable.
make -C C/

## Step 3: Generate YAML from C
Run the compiled C program to generate generated.yml from the data in instructions.h.
./C/yaml_emitter generated.yml
## Step 4: Verify Idempotency (Round-trip)
To verify that the process is idempotent, repeat the steps using generated.yml as the input.
# 1. Generate a new header from the generated YAML
python python/yaml_to_c.py generated.yml C/instructions_roundtrip.h

# 2. Re-compile the C program (it will now use the new header)
make -C C/ HEADER_FILE=instructions_roundtrip.h

# 3. Generate the final YAML
./C/yaml_emitter final.yml

# 4. Compare the two generated YAML files
diff generated.yml final.yml
If diff produces no output, the round-trip conversion was successful, and the process is idempotent.
---

### **`data/rv32i.yml`**

This file contains a simplified representation of two RISC-V instructions, `lui` and `auipc`, based on the structure found in the RISC-V Unified Database.

```yaml
lui:
  description: "Load Upper Immediate"
  isa: "RV32I"
  format: "U-Type"
  opcode: "0110111"
  variable_fields:
    - name: "rd"
      width: 5
    - name: "imm[31:12]"
      width: 20

auipc:
  description: "Add Upper Immediate to PC"
  isa: "RV32I"
  format: "U-Type"
  opcode: "0010111"
  variable_fields:
    - name: "rd"
      width: 5
    - name: "imm[31:12]"
      width: 20
