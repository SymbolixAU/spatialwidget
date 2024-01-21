# v0.2.5

* changed to MIT license
* removed C++11 system requirements
* Replaced `std::regex_match` in `is_hex()` due to crashes on Windows [issue 359](https://github.com/SymbolixAU/mapdeck/issues/359)

# v0.2.4

* create_interleaved() C++ function for formatting interleaved objects

# v0.2.3

* Links to geometries
* setting jsonify unbox to false for columnar data, so JSON is always an array

# v0.2.2

* colours returned as either hex strings or RGBA matrix
* factors maintained as-is (reverting 0.2.1) and used in summary values
* `legend_digits` argument exposed throug api
* `digits` argument exposed through api
* integer matrix palettes supported
* BH -DBOOST_NO_AUTO_PTR flag
* removed sf and jsonlite suggets

# v0.2.1

* factors now converted to strings by default

# v0.2

* Allow list palettes
* Removed `data_types` parameter
* Added a `NEWS.md` file to track changes to the package.
