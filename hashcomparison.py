import hashlib

def hash_file(file_path):
    """Generate the SHA-256 hash of a file..."""
    sha256 = hashlib.sha256() # Create the hash, using haslib for this demo
    try:
        with open(file_path, "rb") as file:
            while chunk := file.read(8192):  # Reading the file in eight kilobyte chunks.
                sha256.update(chunk)
        return sha256.hexdigest()
    except FileNotFoundError:
        print("The file was not found. Please check file naming, path directory, or program structure.")
        return None

def compare_hashes(original_hash, new_file_path):
    """Compare the original hash with the hash of a new file..."""
    new_file_hash = hash_file(new_file_path)
    if not new_file_hash:
        return False
    return original_hash == new_file_hash

# Main method example:
if __name__ == "__main__":
    # File path for demonstration
    original_file = "example.txt" # starting here
    altered_file = "example_altered.txt" # the different file

    # Generate hash for the original file
    original_hash = hash_file(original_file)
    print(f"Original File Hash: {original_hash}")

    # Compare the hash of an unaltered file
    print("\nComparing with an unaltered file...")
    if compare_hashes(original_hash, original_file):
        print("The file is intact.")
    else:
        print("The file has been altered.")

    # Compare the hash of an altered file
    print("\nComparing with an altered file...")
    if compare_hashes(original_hash, altered_file):
        print("The file is intact.")
    else:
        print("The file has been altered.")
