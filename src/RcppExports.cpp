// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

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
Rcpp::List rcpp_colour_str_with_palette(SEXP palette, Rcpp::StringVector fill_colour_vec, Rcpp::NumericVector alpha, std::string na_colour, bool include_alpha);
RcppExport SEXP _spatialwidget_rcpp_colour_str_with_palette(SEXP paletteSEXP, SEXP fill_colour_vecSEXP, SEXP alphaSEXP, SEXP na_colourSEXP, SEXP include_alphaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type palette(paletteSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type fill_colour_vec(fill_colour_vecSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type na_colour(na_colourSEXP);
    Rcpp::traits::input_parameter< bool >::type include_alpha(include_alphaSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_colour_str_with_palette(palette, fill_colour_vec, alpha, na_colour, include_alpha));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_colour_num_with_palette
Rcpp::List rcpp_colour_num_with_palette(SEXP palette, Rcpp::NumericVector fill_colour_vec, Rcpp::NumericVector alpha, std::string na_colour, bool include_alpha);
RcppExport SEXP _spatialwidget_rcpp_colour_num_with_palette(SEXP paletteSEXP, SEXP fill_colour_vecSEXP, SEXP alphaSEXP, SEXP na_colourSEXP, SEXP include_alphaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type palette(paletteSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type fill_colour_vec(fill_colour_vecSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type na_colour(na_colourSEXP);
    Rcpp::traits::input_parameter< bool >::type include_alpha(include_alphaSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_colour_num_with_palette(palette, fill_colour_vec, alpha, na_colour, include_alpha));
    return rcpp_result_gen;
END_RCPP
}
// spatialwidget_geojson
Rcpp::List spatialwidget_geojson(Rcpp::DataFrame data, Rcpp::List data_types, Rcpp::List params, Rcpp::List defaults, Rcpp::StringMatrix colours, Rcpp::StringVector legend, Rcpp::StringVector geometry);
RcppExport SEXP _spatialwidget_spatialwidget_geojson(SEXP dataSEXP, SEXP data_typesSEXP, SEXP paramsSEXP, SEXP defaultsSEXP, SEXP coloursSEXP, SEXP legendSEXP, SEXP geometrySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type data_types(data_typesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type defaults(defaultsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringMatrix >::type colours(coloursSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type legend(legendSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry(geometrySEXP);
    rcpp_result_gen = Rcpp::wrap(spatialwidget_geojson(data, data_types, params, defaults, colours, legend, geometry));
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
// rcpp_widget_line
Rcpp::List rcpp_widget_line(Rcpp::DataFrame data, Rcpp::List data_types, Rcpp::List params, Rcpp::StringVector geometry_columns);
RcppExport SEXP _spatialwidget_rcpp_widget_line(SEXP dataSEXP, SEXP data_typesSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type data_types(data_typesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_line(data, data_types, params, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_point
Rcpp::List rcpp_widget_point(Rcpp::DataFrame data, Rcpp::List data_types, Rcpp::List params, Rcpp::StringVector geometry_columns);
RcppExport SEXP _spatialwidget_rcpp_widget_point(SEXP dataSEXP, SEXP data_typesSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type data_types(data_typesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_point(data, data_types, params, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_point_df
Rcpp::List rcpp_widget_point_df(Rcpp::DataFrame data, Rcpp::List data_types, Rcpp::List params, Rcpp::List geometries);
RcppExport SEXP _spatialwidget_rcpp_widget_point_df(SEXP dataSEXP, SEXP data_typesSEXP, SEXP paramsSEXP, SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type data_types(data_typesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_point_df(data, data_types, params, geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_widget_polygon
Rcpp::List rcpp_widget_polygon(Rcpp::DataFrame data, Rcpp::List data_types, Rcpp::List params, Rcpp::StringVector geometry_columns);
RcppExport SEXP _spatialwidget_rcpp_widget_polygon(SEXP dataSEXP, SEXP data_typesSEXP, SEXP paramsSEXP, SEXP geometry_columnsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type data_types(data_typesSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geometry_columns(geometry_columnsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_widget_polygon(data, data_types, params, geometry_columns));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_spatialwidget_rcpp_construct_data", (DL_FUNC) &_spatialwidget_rcpp_construct_data, 6},
    {"_spatialwidget_rcpp_resolve_palette", (DL_FUNC) &_spatialwidget_rcpp_resolve_palette, 2},
    {"_spatialwidget_rcpp_colour_str_with_palette", (DL_FUNC) &_spatialwidget_rcpp_colour_str_with_palette, 5},
    {"_spatialwidget_rcpp_colour_num_with_palette", (DL_FUNC) &_spatialwidget_rcpp_colour_num_with_palette, 5},
    {"_spatialwidget_spatialwidget_geojson", (DL_FUNC) &_spatialwidget_spatialwidget_geojson, 7},
    {"_spatialwidget_rcpp_fill_vector", (DL_FUNC) &_spatialwidget_rcpp_fill_vector, 4},
    {"_spatialwidget_rcpp_where_is", (DL_FUNC) &_spatialwidget_rcpp_where_is, 2},
    {"_spatialwidget_rcpp_remove_list_elements", (DL_FUNC) &_spatialwidget_rcpp_remove_list_elements, 2},
    {"_spatialwidget_rcpp_widget_line", (DL_FUNC) &_spatialwidget_rcpp_widget_line, 4},
    {"_spatialwidget_rcpp_widget_point", (DL_FUNC) &_spatialwidget_rcpp_widget_point, 4},
    {"_spatialwidget_rcpp_widget_point_df", (DL_FUNC) &_spatialwidget_rcpp_widget_point_df, 4},
    {"_spatialwidget_rcpp_widget_polygon", (DL_FUNC) &_spatialwidget_rcpp_widget_polygon, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_spatialwidget(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
