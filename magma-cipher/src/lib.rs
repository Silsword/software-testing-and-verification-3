use hex_literal::hex;
use magma::cipher::generic_array::ArrayLength;
use magma::cipher::{
    generic_array::{typenum::U8, GenericArray},
    BlockDecrypt, BlockEncrypt, KeyInit,
};
use magma::Magma;
use rand::prelude::*;

use std::os::raw;

enum Status {
    Encrypted(Vec<u8>),
    Decrypted(Vec<u8>),
}

#[no_mangle]
pub extern "C" fn encrypt(path: *const raw::c_char) -> *const raw::c_ulonglong {
    todo!()
}

#[no_mangle]
pub extern "C" fn decrypt(path: *const raw::c_char, key: *const raw::c_ulonglong) -> raw::c_int {
    todo!()
}

fn generate_key() -> Vec<u8> {
    todo!()
}

fn encrypt_array(arr: Vec<u8>, key: Vec<u8>) -> Vec<u8> {
    let cipher = Magma::new(key.as_slice().into());
    let mut arr = arr;
    for i in 0..(arr.len() % 8) {
        arr.push(0);
    }
    let mut chunks: Vec<&[u8]> = arr.chunks(8).collect();
    let mut ret = Vec::new();
    for i in chunks.iter() {
        let mut block = GenericArray::clone_from_slice(*i);
	cipher.encrypt_block(&mut block);
	let mut block = block.to_vec();
	ret.append(&mut block);
    }
    ret
}

fn decrypt_array(arr: Vec<u8>, key: Vec<u8>) -> Vec<u8> {
    todo!()
}

fn bytes_from_file(path: &str) -> Vec<u8> {
    todo!()
}

fn bytes_to_file(path: &str, status: Status) {
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_encrypt_array() {
        let key = hex!("FFEEDDCCBBAA99887766554433221100"
		       "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF");
        let arr = hex!("FEDCBA9876543210");
        let ciph_arr: Vec<u8> = hex!("4EE901E5C2D8CA3D").into();

        let arr = encrypt_array(arr.into(), key.into());
        assert_eq!(arr, ciph_arr);
    }
}
