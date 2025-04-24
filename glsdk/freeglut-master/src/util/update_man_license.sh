#!/bin/bash

LICENSE_TEXT=$(cat <<'EOF'
print ".\\\"";
print ".\\\" Permission is hereby granted, free of charge, to any person obtaining a copy";
print ".\\\" of this software and associated documentation files (the \"Software\"), to deal";
print ".\\\" in the Software without restriction, including without limitation the rights";
print ".\\\" to use, copy, modify, merge, publish, distribute, sublicense, and/or sell";
print ".\\\" copies of the Software, and to permit persons to whom the Software is";
print ".\\\" furnished to do so, subject to the following conditions:";
print ".\\\"";
print ".\\\" The above copyright notice and this permission notice shall be included in";
print ".\\\" all copies or substantial portions of the Software.";
print ".\\\"";
print ".\\\" THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR";
print ".\\\" IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,";
print ".\\\" FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL";
print ".\\\" MARK J. KILGARD BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER";
print ".\\\" IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN";
print ".\\\" CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.";
EOF
)

LICENSE_REFERENCE=$(cat <<'EOF'
print ".\\\"";
print ".\\\" See the file \"man/LICENSE\" for information on usage and redistribution";
EOF
)

# Locate the FreeGLUT directory regardless of the current working directory
FREEGLUT_DIR=$(readlink -f "$0" | grep -o ".*freeglut[^/]*")

if [ -z "$FREEGLUT_DIR" ]; then
    echo "Error: FreeGLUT directory not found."
    exit 1
fi

for file in "${FREEGLUT_DIR}"/man/*.man; do
    echo "Updating $file..."
    temp_file=$(mktemp)

    # Update the license if needed
    if grep -q "Permission is hereby granted\|See the file \"man/LICENSE\" for" "$file"; then
        echo "  License already exists, skipping license update"
        cp "$file" "$temp_file"
    else
        echo "  Adding license reference"
        awk "
        /Copyright \(c\) Mark J. Kilgard/ {
            print \$0;
            $LICENSE_REFERENCE
            next;
        }
        { print \$0; }
        " "$file" > "$temp_file"
    fi

    # Create a second temp file for the header update
    temp_file2=$(mktemp)

    # Update the man page header (.TH) line
    echo "  Updating header date to April 2025"
    awk '
    /^\.TH/ {
        # Extract the command name and keep it
        command = $2
        # Replace with updated format (command, section, date, source, manual)
        print ".TH", command, "3", "\"April 2025\"", "\"freeglut\"", "\"freeglut\"" 
        next
    }
    { print $0 }
    ' "$temp_file" > "$temp_file2"

    # Move the final result back to the original file
    mv "$temp_file2" "$file"
    rm "$temp_file"
done

echo "Man page update complete!"
