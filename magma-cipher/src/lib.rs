use magma::Magma;
use magma::cipher::{
    generic_array::GenericArray,
    BlockEncrypt, BlockDecrypt, KeyInit
};
use rand::prelude::*;

use std::os::raw;

enum Status {
    Encrypted(Vec<u8>),
    Decrypted(Vec<u8>)
}

#[no_mangle]
pub extern "C" fn encrypt(path : *const raw::c_char) -> *const raw::c_ulonglong {
     todo!()
}

#[no_mangle]
pub extern "C" fn decrypt(path : *const raw::c_char, key : *const raw::c_ulonglong) -> raw::c_int {
    todo!()
}

fn generate_key() -> Vec<u8> {
    todo!()
}

fn encrypt_array(arr : Vec<u8>, key : Vec<u8>) -> Vec<u8> {
    todo!()
}

fn decrypt_array(arr : Vec<u8>, key : Vec<u8>) -> Vec<u8> {
    todo!()
}

fn bytes_from_file(path : &str) -> Vec<u8> {
    todo!()
}

fn bytes_to_file(path : &str, status : Status) {
    todo!()
}
