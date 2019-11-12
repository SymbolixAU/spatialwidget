// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rcpp_make_colours
Rcpp::List rcpp_make_colours(Rcpp::List& lst_params, Rcpp::List& params, Rcpp::DataFrame& data, Rcpp::List& lst_defaults, int col_index, SEXP& palette_type, Rcpp::NumericVector& alpha, std::string& colour_name, bool& include_legend, int legend_digits, std::string colour_format);
RcppExport SEXP _spatialwidget_rcpp_make_colours(SEXP lst_paramsSEXP, SEXP paramsSEXP, SEXP dataSEXP, SEXP lst_defaultsSEXP, SEXP col_indexSEXP, SEXP palette_typeSEXP, SEXP alphaSEXP, SEXP colour_nameSEXP, SEXP include_legendSEXP, SEXP legend_digitsSEXP, SEXP colour_formatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_params(lst_paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_defaults(lst_defaultsSEXP);
    Rcpp::traits::input_parameter< int >::type col_index(col_indexSEXP);
    Rcpp::traits::input_parameter< SEXP& >::type palette_type(palette_typeSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector& >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string& >::type colour_name(colour_nameSEXP);
    Rcpp::traits::input_parameter< bool& >::type include_legend(include_legendSEXP);
    Rcpp::traits::input_parameter< int >::type legend_digits(legend_digitsSEXP);
    Rcpp::traits::input_parameter< std::string >::type colour_format(colour_formatSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_make_colours(lst_params, params, data, lst_defaults, col_index, palette_type, alpha, colour_name, include_legend, legend_digits, colour_format));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_resolve_colour
Rcpp::List rcpp_resolve_colour(Rcpp::List& lst_params, Rcpp::List& params, Rcpp::DataFrame& data, Rcpp::List& lst_defaults, std::string& colour_name, std::string& opacity_name, Rcpp::List& lst_legend, bool& include_legend, std::string colour_format);
RcppExport SEXP _spatialwidget_rcpp_resolve_colour(SEXP lst_paramsSEXP, SEXP paramsSEXP, SEXP dataSEXP, SEXP lst_defaultsSEXP, SEXP colour_nameSEXP, SEXP opacity_nameSEXP, SEXP lst_legendSEXP, SEXP include_legendSEXP, SEXP colour_formatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_params(lst_paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_defaults(lst_defaultsSEXP);
    Rcpp::traits::input_parameter< std::string& >::type colour_name(colour_nameSEXP);
    Rcpp::traits::input_parameter< std::string& >::type opacity_name(opacity_nameSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_legend(lst_legendSEXP);
    Rcpp::traits::input_parameter< bool& >::type include_legend(include_legendSEXP);
    Rcpp::traits::input_parameter< std::string >::type colour_format(colour_formatSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_resolve_colour(lst_params, params, data, lst_defaults, colour_name, opacity_name, lst_legend, include_legend, colour_format));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_construct_data
Rcpp::DataFrame rcpp_construct_data(Rcpp::StringVector param_names, Rcpp::List params, Rcpp::StringVector data_names, Rcpp::List lst_defaults, Rcpp::DataFrame data, int data_rows);
RcppExport SEXP _spatialwidget_rcpp_construct_data(SEXP param_namesSEXP, SEXP paramsSEXP, SEXP data_namesSEXP, SEXP lst_defaultsSEXP, SEXP dataSEXP, SEXP data_rowsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type param_names(param_namesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type data_names(data_namesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type lst_defaults(lst_defaultsSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< int >::type data_rows(data_rowsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_construct_data(param_names, params, data_names, lst_defaults, data, data_rows));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson
Rcpp::StringVector rcpp_geojson(Rcpp::DataFrame sf, std::string geometry);
RcppExport SEXP _spatialwidget_rcpp_geojson(SEXP sfSEXP, SEXP geometrySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type sf(sfSEXP);
    Rcpp::traits::input_parameter< std::string >::type geometry(geometrySEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson(sf, geometry));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson_sf
Rcpp::StringVector rcpp_geojson_sf(Rcpp::DataFrame sf, Rcpp::StringVector geometries);
RcppExport SEXP _spatialwidget_rcpp_geojson_sf(SEXP sfSEXP, SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type sf(sfSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_sf(sf, geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson_df
Rcpp::StringVector rcpp_geojson_df(Rcpp::DataFrame df, Rcpp::List geometries);
RcppExport SEXP _spatialwidget_rcpp_geojson_df(SEXP dfSEXP, SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_df(df, geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson_dfz
Rcpp::StringVector rcpp_geojson_dfz(Rcpp::DataFrame df, Rcpp::List geometries);
RcppExport SEXP _spatialwidget_rcpp_geojson_dfz(SEXP dfSEXP, SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_dfz(df, geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_sf_to_geojson_downcast
Rcpp::StringVector rcpp_sf_to_geojson_downcast(Rcpp::DataFrame sf, std::string geometry_column);
RcppExport SEXP _spatialwidget_rcpp_sf_to_geojson_downcast(SEXP sfSEXP, SEXP geometry_columnSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type sf(sfSEXP);
    Rcpp::traits::input_parameter< std::string >::type geometry_column(geometry_columnSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_sf_to_geojson_downcast(sf, geometry_column));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_sf_to_geojson_multi_column_downcast
Rcpp::StringVector rcpp_sf_to_geojson_multi_column_downcast(Rcpp::DataFrame sf, Rcpp::StringVector geometries);
RcppExport SEXP _spatialwidget_rcpp_sf_to_geojson_multi_column_downcast(SEXP sfSEXP, SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type sf(sfSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_sf_to_geojson_multi_column_downcast(sf, geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_construct_legend_list
Rcpp::List rcpp_construct_legend_list(Rcpp::List& lst_params, Rcpp::List& params, Rcpp::StringVector& param_names, Rcpp::StringVector& legend_types);
RcppExport SEXP _spatialwidget_rcpp_construct_legend_list(SEXP lst_paramsSEXP, SEXP paramsSEXP, SEXP param_namesSEXP, SEXP legend_typesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_params(lst_paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type param_names(param_namesSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector& >::type legend_types(legend_typesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_construct_legend_list(lst_params, params, param_names, legend_types));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_set_legend_option
std::string rcpp_set_legend_option(Rcpp::List& opts, std::string& option, std::string value, std::string& colour_name);
RcppExport SEXP _spatialwidget_rcpp_set_legend_option(SEXP optsSEXP, SEXP optionSEXP, SEXP valueSEXP, SEXP colour_nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type opts(optsSEXP);
    Rcpp::traits::input_parameter< std::string& >::type option(optionSEXP);
    Rcpp::traits::input_parameter< std::string >::type value(valueSEXP);
    Rcpp::traits::input_parameter< std::string& >::type colour_name(colour_nameSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_set_legend_option(opts, option, value, colour_name));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_geojson_mesh
Rcpp::StringVector rcpp_to_geojson_mesh(Rcpp::List& mesh, Rcpp::StringVector vertices);
RcppExport SEXP _spatialwidget_rcpp_to_geojson_mesh(SEXP meshSEXP, SEXP verticesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type mesh(meshSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type vertices(verticesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_geojson_mesh(mesh, vertices));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_resolve_palette
Rcpp::StringVector rcpp_resolve_palette(Rcpp::List lst_params, Rcpp::List params);
RcppExport SEXP _spatialwidget_rcpp_resolve_palette(SEXP lst_paramsSEXP, SEXP paramsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type lst_params(lst_paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_resolve_palette(lst_params, params));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_colour_str_with_palette
Rcpp::List rcpp_colour_str_with_palette(SEXP palette, SEXP fill_colour_vec, Rcpp::NumericVector alpha, std::string na_colour, bool include_alpha, std::string colour_name);
RcppExport SEXP _spatialwidget_rcpp_colour_str_with_palette(SEXP paletteSEXP, SEXP fill_colour_vecSEXP, SEXP alphaSEXP, SEXP na_colourSEXP, SEXP include_alphaSEXP, SEXP colour_nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type palette(paletteSEXP);
    Rcpp::traits::input_parameter< SEXP >::type fill_colour_vec(fill_colour_vecSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type na_colour(na_colourSEXP);
    Rcpp::traits::input_parameter< bool >::type include_alpha(include_alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type colour_name(colour_nameSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_colour_str_with_palette(palette, fill_colour_vec, alpha, na_colour, include_alpha, colour_name));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_colour_num_with_palette
Rcpp::List rcpp_colour_num_with_palette(SEXP palette, SEXP fill_colour_vec, Rcpp::NumericVector alpha, std::string na_colour, bool include_alpha, std::string colour_name, int legend_digits);
RcppExport SEXP _spatialwidget_rcpp_colour_num_with_palette(SEXP paletteSEXP, SEXP fill_colour_vecSEXP, SEXP alphaSEXP, SEXP na_colourSEXP, SEXP include_alphaSEXP, SEXP colour_nameSEXP, SEXP legend_digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type palette(paletteSEXP);
    Rcpp::traits::input_parameter< SEXP >::type fill_colour_vec(fill_colour_vecSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type na_colour(na_colourSEXP);
    Rcpp::traits::input_parameter< bool >::type include_alpha(include_alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type colour_name(colour_nameSEXP);
    Rcpp::traits::input_parameter< int >::type legend_digits(legend_digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_colour_num_with_palette(palette, fill_colour_vec, alpha, na_colour, include_alpha, colour_name, legend_digits));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_construct_params
Rcpp::List rcpp_construct_params(Rcpp::DataFrame& data, Rcpp::List& params);
RcppExport SEXP _spatialwidget_rcpp_construct_params(SEXP dataSEXP, SEXP paramsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type params(paramsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_construct_params(data, params));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_params_to_data
Rcpp::List rcpp_params_to_data(Rcpp::DataFrame& data, Rcpp::List& params, Rcpp::List& lst_defaults, Rcpp::StringVector layer_legend, int data_rows, Rcpp::StringVector parameter_exclusions, bool factors_as_string);
RcppExport SEXP _spatialwidget_rcpp_params_to_data(SEXP dataSEXP, SEXP paramsSEXP, SEXP lst_defaultsSEXP, SEXP layer_legendSEXP, SEXP data_rowsSEXP, SEXP parameter_exclusionsSEXP, SEXP factors_as_stringSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type lst_defaults(lst_defaultsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type layer_legend(layer_legendSEXP);
    Rcpp::traits::input_parameter< int >::type data_rows(data_rowsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type parameter_exclusions(parameter_exclusionsSEXP);
    Rcpp::traits::input_parameter< bool >::type factors_as_string(factors_as_stringSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_params_to_data(data, params, lst_defaults, layer_legend, data_rows, parameter_exclusions, factors_as_string));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_fill_vector
Rcpp::List rcpp_fill_vector(Rcpp::List lst_defaults, Rcpp::String param_name, SEXP value, int n_rows);
RcppExport SEXP _spatialwidget_rcpp_fill_vector(SEXP lst_defaultsSEXP, SEXP param_nameSEXP, SEXP valueSEXP, SEXP n_rowsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type lst_defaults(lst_defaultsSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type param_name(param_nameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type value(valueSEXP);
    Rcpp::traits::input_parameter< int >::type n_rows(n_rowsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_fill_vector(lst_defaults, param_name, value, n_rows));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_where_is
Rcpp::IntegerVector rcpp_where_is(Rcpp::StringVector to_find, Rcpp::StringVector sv);
RcppExport SEXP _spatialwidget_rcpp_where_is(SEXP to_findSEXP, SEXP svSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type to_find(to_findSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type sv(svSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_where_is(to_find, sv));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_remove_list_elements
Rcpp::List rcpp_remove_list_elements(Rcpp::List lst, Rcpp::StringVector to_remove);
RcppExport SEXP _spatialwidget_rcpp_remove_list_elements(SEXP lstSEXP, SEXP to_removeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type lst(lstSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type to_remove(to_removeSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_remove_list_elements(lst, to_remove));
    return rcpp_result_gen;
END_RCPP
}
// is_hex
Rcpp::LogicalVector is_hex(std::string hex_str);
RcppExport SEXP _spatialwidget_is_hex(SEXP hex_strSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type hex_str(hex_strSEXP);
    rcpp_result_gen = Rcpp::wrap(is_hex(hex_str));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_line
Rcpp::List rcpp_widget_line(Rcpp::DataFrame data, Rcpp::List params, Rcpp::StringVector geometry_columns, bool jsonify_legend, int digits);
RcppExport SEXP _spatialwidget_rcpp_widget_line(SEXP dataSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP, SEXP jsonify_legendSEXP, SEXP digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< bool >::type jsonify_legend(jsonify_legendSEXP);
    Rcpp::traits::input_parameter< int >::type digits(digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_line(data, params, geometry_columns, jsonify_legend, digits));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_point
Rcpp::List rcpp_widget_point(Rcpp::DataFrame data, Rcpp::List params, Rcpp::StringVector geometry_columns, bool jsonify_legend, int digits);
RcppExport SEXP _spatialwidget_rcpp_widget_point(SEXP dataSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP, SEXP jsonify_legendSEXP, SEXP digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< bool >::type jsonify_legend(jsonify_legendSEXP);
    Rcpp::traits::input_parameter< int >::type digits(digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_point(data, params, geometry_columns, jsonify_legend, digits));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_point_df
Rcpp::List rcpp_widget_point_df(Rcpp::DataFrame data, Rcpp::List params, Rcpp::List geometries, bool jsonify_legend, int digits);
RcppExport SEXP _spatialwidget_rcpp_widget_point_df(SEXP dataSEXP, SEXP paramsSEXP, SEXP geometriesSEXP, SEXP jsonify_legendSEXP, SEXP digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type geometries(geometriesSEXP);
    Rcpp::traits::input_parameter< bool >::type jsonify_legend(jsonify_legendSEXP);
    Rcpp::traits::input_parameter< int >::type digits(digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_point_df(data, params, geometries, jsonify_legend, digits));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_point_df_binary
Rcpp::List rcpp_widget_point_df_binary(Rcpp::DataFrame data, Rcpp::List params, Rcpp::List geometries, bool jsonify_legend, int digits);
RcppExport SEXP _spatialwidget_rcpp_widget_point_df_binary(SEXP dataSEXP, SEXP paramsSEXP, SEXP geometriesSEXP, SEXP jsonify_legendSEXP, SEXP digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type geometries(geometriesSEXP);
    Rcpp::traits::input_parameter< bool >::type jsonify_legend(jsonify_legendSEXP);
    Rcpp::traits::input_parameter< int >::type digits(digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_point_df_binary(data, params, geometries, jsonify_legend, digits));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_polygon
Rcpp::List rcpp_widget_polygon(Rcpp::DataFrame data, Rcpp::List params, Rcpp::StringVector geometry_columns, bool jsonify_legend, int digits);
RcppExport SEXP _spatialwidget_rcpp_widget_polygon(SEXP dataSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP, SEXP jsonify_legendSEXP, SEXP digitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    Rcpp::traits::input_parameter< bool >::type jsonify_legend(jsonify_legendSEXP);
    Rcpp::traits::input_parameter< int >::type digits(digitsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_polygon(data, params, geometry_columns, jsonify_legend, digits));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_spatialwidget_rcpp_make_colours", (DL_FUNC) &_spatialwidget_rcpp_make_colours, 11},
    {"_spatialwidget_rcpp_resolve_colour", (DL_FUNC) &_spatialwidget_rcpp_resolve_colour, 9},
    {"_spatialwidget_rcpp_construct_data", (DL_FUNC) &_spatialwidget_rcpp_construct_data, 6},
    {"_spatialwidget_rcpp_geojson", (DL_FUNC) &_spatialwidget_rcpp_geojson, 2},
    {"_spatialwidget_rcpp_geojson_sf", (DL_FUNC) &_spatialwidget_rcpp_geojson_sf, 2},
    {"_spatialwidget_rcpp_geojson_df", (DL_FUNC) &_spatialwidget_rcpp_geojson_df, 2},
    {"_spatialwidget_rcpp_geojson_dfz", (DL_FUNC) &_spatialwidget_rcpp_geojson_dfz, 2},
    {"_spatialwidget_rcpp_sf_to_geojson_downcast", (DL_FUNC) &_spatialwidget_rcpp_sf_to_geojson_downcast, 2},
    {"_spatialwidget_rcpp_sf_to_geojson_multi_column_downcast", (DL_FUNC) &_spatialwidget_rcpp_sf_to_geojson_multi_column_downcast, 2},
    {"_spatialwidget_rcpp_construct_legend_list", (DL_FUNC) &_spatialwidget_rcpp_construct_legend_list, 4},
    {"_spatialwidget_rcpp_set_legend_option", (DL_FUNC) &_spatialwidget_rcpp_set_legend_option, 4},
    {"_spatialwidget_rcpp_to_geojson_mesh", (DL_FUNC) &_spatialwidget_rcpp_to_geojson_mesh, 2},
    {"_spatialwidget_rcpp_resolve_palette", (DL_FUNC) &_spatialwidget_rcpp_resolve_palette, 2},
    {"_spatialwidget_rcpp_colour_str_with_palette", (DL_FUNC) &_spatialwidget_rcpp_colour_str_with_palette, 6},
    {"_spatialwidget_rcpp_colour_num_with_palette", (DL_FUNC) &_spatialwidget_rcpp_colour_num_with_palette, 7},
    {"_spatialwidget_rcpp_construct_params", (DL_FUNC) &_spatialwidget_rcpp_construct_params, 2},
    {"_spatialwidget_rcpp_params_to_data", (DL_FUNC) &_spatialwidget_rcpp_params_to_data, 7},
    {"_spatialwidget_rcpp_fill_vector", (DL_FUNC) &_spatialwidget_rcpp_fill_vector, 4},
    {"_spatialwidget_rcpp_where_is", (DL_FUNC) &_spatialwidget_rcpp_where_is, 2},
    {"_spatialwidget_rcpp_remove_list_elements", (DL_FUNC) &_spatialwidget_rcpp_remove_list_elements, 2},
    {"_spatialwidget_is_hex", (DL_FUNC) &_spatialwidget_is_hex, 1},
    {"_spatialwidget_rcpp_widget_line", (DL_FUNC) &_spatialwidget_rcpp_widget_line, 5},
    {"_spatialwidget_rcpp_widget_point", (DL_FUNC) &_spatialwidget_rcpp_widget_point, 5},
    {"_spatialwidget_rcpp_widget_point_df", (DL_FUNC) &_spatialwidget_rcpp_widget_point_df, 5},
    {"_spatialwidget_rcpp_widget_point_df_binary", (DL_FUNC) &_spatialwidget_rcpp_widget_point_df_binary, 5},
    {"_spatialwidget_rcpp_widget_polygon", (DL_FUNC) &_spatialwidget_rcpp_widget_polygon, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_spatialwidget(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
