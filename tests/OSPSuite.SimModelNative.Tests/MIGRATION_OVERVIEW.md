# Migration overview: old C++/CLI tests &rarr; native Google Test

This document tracks the migration of the old C++/CLI unit tests (commit
`d28cbbc01299c08ee773acaa657e1cc2811b20b0`, folder
`tests/OSPSuite.SimModel.Tests/src`) to the new pure-native Google Test
project `tests/OSPSuite.SimModelNative.Tests/src`.

Conventions used for the migrated tests follow the existing native specs
(`TEST(when_doing_something, should_be_this_and_that)` /
`TEST_F(when_..., should_...)`). "Helper" files contain no tests of their own;
their extender classes (public-inheritance accessors for protected members) were
inlined into the corresponding main test file.

Only the native test project (`OSPSuite.SimModelNative.Tests`) was modified. Per
the task constraint, tests that cannot run without modifying other projects were
**not** added.

---

## ExplicitFormulaSpecs.cpp

Migrated to **`src/ExplicitFormulaSpecs.cpp`** (new). The extender classes from
`ExplicitFormulaSpecsHelper.cpp` were inlined. `XMLHelper::ToString` (which pulls
in the XML backend) was replaced by a local `FormatNumber()` helper.

| Old test (context :: method) | Added | Comment |
|---|---|---|
| when_creating_for_references_independent_equation :: should_calculate_correct_value | YES | Free `TEST`. |
| when_creating_for_parameter_and_species_references :: should_calculate_correct_value_without_simplifying | YES | |
| when_creating_for_parameter_and_species_references :: should_calculate_correct_value_with_simplifying | YES | |
| when_creating_for_parameter_species_and_time :: should_calculate_correct_value_without_simplifying | YES | |
| when_creating_for_parameter_species_and_time :: should_calculate_correct_value_with_simplifying | YES | |
| when_getting_switch_timepoints :: should_return_correct_switch_timepoints | YES | |
| when_creating_product_formula (context) | NO | The context contained no `[TestAttribute]` methods in the old file, so there is nothing to migrate. |

## ExplicitFormulaSpecsHelper.cpp

| Old item | Added | Comment |
|---|---|---|
| (extender classes only) | n/a | Contains no tests. Extenders (`ParameterExtender`, `SpeciesExtender`, `QuantityReferenceExtender`, `ExplicitFormulaExtender`) were inlined into `src/ExplicitFormulaSpecs.cpp`. |

## OutputSchemaSpecs.cpp

Integrated into the existing **`src/OutputSchemaSpecs.cpp`**.

| Old test | Added | Comment |
|---|---|---|
| when_retrieving_all_points_from_output_schema_with_overlapping_intervals :: should_retrieve_all_points | YES | Added as `when_retrieving_points_from_output_schema_with_overlapping_intervals / should_retrieve_all_unique_points_in_increasing_order`, exercising `OutputSchema::AllTimePoints<float>()`. |

## ParameterSpecs.cpp

Migrated to **`src/ParameterSpecs.cpp`** (new).

| Old test | Added | Comment |
|---|---|---|
| when_setting_table_points_into_nontable_parameter :: parameter_should_be_table | YES | |
| when_setting_table_points_into_nontable_parameter :: should_calculate_correct_value | YES | Direct-interpolation values (`SetTablePoints` builds a table with `UseDerivedValues=false`). |
| when_setting_initial_value_into_table_parameter :: parameter_should_not_be_table | YES | |
| when_setting_initial_value_into_table_parameter :: should_calculate_correct_value | YES | |

## RcmSpecs.cpp

Integrated into the existing **`src/RcmSpecs.cpp`**. Added an `RcmExtender`
(public accessor for the protected `createAdjacencyInfo`) plus a
`createTenNodeMatrix()` helper.

| Old test | Added | Comment |
|---|---|---|
| should_create_proper_rcm_inputs | YES | |
| should_return_correct_permutation | YES | Added as `should_return_correct_permutation_for_ten_node_example`. |

## SimulationTaskSpecs.cpp

Migrated to **`src/SimulationTaskSpecs.cpp`** (new). A `SimulationTaskExtender`
exposes the protected static `OutputTimePoints`.

| Old test | Added | Comment |
|---|---|---|
| should_return_usertimepoints_for_empty_switch_timepoints | YES | |
| should_return_correct_timepoints_1 | YES | |
| should_return_correct_timepoints_2 | YES | |
| should_return_correct_timepoints_3 | YES | |
| should_return_correct_timepoints_4 | YES | |
| should_return_correct_timepoints_5 | YES | |

## TableFormulaSpecs.cpp

Migrated to **`src/TableFormulaSpecs.cpp`** (new). A `TableFormulaExtender`
exposes `_valuePoints` and `CacheValues`.

| Old test | Added | Comment |
|---|---|---|
| should_calculate_correct_value | YES | |
| should_set_restart_timepoints | YES | |

## TableFormulaWithOffsetSpecs.cpp

Migrated to **`src/TableFormulaWithOffsetSpecs.cpp`** (new).

| Old test | Added | Comment |
|---|---|---|
| should_calculate_correct_value | YES | |
| should_set_restart_timepoints | YES | |

## TableFormulaWithXArgumentSpecs.cpp

Migrated to **`src/TableFormulaWithXArgumentSpecs.cpp`** (new).

| Old test | Added | Comment |
|---|---|---|
| should_calculate_correct_values_in_direct_mode | YES | |
| should_calculate_correct_values_in_derived_mode | YES | |
| should_return_empty_restart_timepoints_set | YES | |

## SpecsHelper.cpp

| Old item | Added | Comment |
|---|---|---|
| (helper code only) | n/a | Contains no tests. This is .NET/managed test-infrastructure (test-data path resolution and result comparison helpers used by `SimulationSpecs.cpp`). It is not migrated; the native project does not have an equivalent simulation/test-data harness. |

## SimModelCompSpecs.cpp

The old `SimModelCompSpecs.cpp` tests the **OSPSuite.SimModelComp** project,
which is a separate project and is **not** linked into the native test project
(`OSPSuite.SimModelNative.Tests`). Adding these tests would require modifying
other projects' build (to link SimModelComp), which the task explicitly
forbids. Per the rule "if because of this constraint any new tests are not
running - do not add them", none were added.

| Old test | Added | Comment |
|---|---|---|
| should_save_only_persistable_variables_and_observers_into_output_table | NO | Tests SimModelComp (not linked by the native test project). |
| should_save_all_variables_and_observers_into_output_table | NO | Tests SimModelComp (not linked). |
| should_perform_two_simulation_runs | NO | Tests SimModelComp (not linked). |
| should_produce_same_results_when_reloaded_from_saved_file (run A) | NO | Tests SimModelComp (not linked). |
| should_perform_simulation_run (run A) | NO | Tests SimModelComp (not linked). |
| should_produce_same_results_when_reloaded_from_saved_file (run B) | NO | Tests SimModelComp (not linked). |
| should_perform_simulation_run (run B) | NO | Tests SimModelComp (not linked). |
| should_solve_example_system_and_return_correct_sensitivity_values | NO | Tests SimModelComp (not linked). |
| should_add_persistable_parameters_as_observers_into_observers_table | NO | Tests SimModelComp (not linked). |
| should_retrieve_version_of_simmodel_and_simmodelcomp | NO | Tests SimModelComp (not linked). |
| should_set_used_in_simulation_flag_correctly | NO | Tests SimModelComp (not linked). |
| should_throw_exception | NO | Tests SimModelComp (not linked). |

## SimModelCompSpecsHelper.cpp

| Old item | Added | Comment |
|---|---|---|
| (helper code only) | n/a | Contains no tests; supports SimModelCompSpecs.cpp, which is out of scope (see above). |

## SimulationSpecs.cpp

These are full simulation **integration** tests (load XML test data &rarr; run
the CVODES solver &rarr; compare against reference results). The large majority
were already migrated to **`tests/OSPSuite.SimModel.Tests/SimulationSpecs.cs`**
and must not be duplicated. The remainder are either managed-only XML/API tests,
or integration tests that depend on the .NET test-data / reference-comparison
harness (`SpecsHelper.cpp`) which has no equivalent in the native test project
and cannot be reproduced without modifying other projects.

**None were added to the native project.** See the per-test comments below.

| Old test (context :: method) | Added | Comment |
|---|---|---|
| when_loading_from_file :: should_be_loaded_from_file | NO | Already in C# (`when_loading_simulation_from_file`). |
| when_loading_from_string :: should_be_loaded_from_file | NO | Already in C# (`when_loading_from_string`). |
| when_loading_and_finalizing_from_file :: should_be_loaded_and_finalized_from_file | NO | Already in C# (`when_loading_simulation_from_file_and_running`). |
| when_loading_finalizing_and_running :: should_perform_simulation_run | NO | Already in C# (`when_loading_simulation_from_file_and_running`). |
| when_loading_finalizing_and_running_band_solver :: should_perform_simulation_run | NO | Integration (band solver) test; needs test-data/reference harness not available in native project. |
| when_running_system_with_all_constant_species_dense :: solver_output_times_should_be_equal_to_output_schema | NO | Already in C# (`when_running_system_with_all_constant_species`). |
| when_running_system_with_all_constant_species_dense :: species_values_should_be_equal_to_initial_value | NO | Already in C# (`when_running_system_with_all_constant_species`). |
| when_running_system_with_all_constant_species_band :: solver_output_times_should_be_equal_to_output_schema | NO | Band variant; integration test, harness not available. |
| when_running_system_with_all_constant_species_band :: species_values_should_be_equal_to_initial_value | NO | Band variant; integration test, harness not available. |
| when_getting_all_parameter_values_and_all_initial_values :: should_return_correct_value_for_dependent_parameters_and_initial_value_before_and_after_changing_of_basis_parameter | NO | Already in C# (`when_getting_all_parameter_values_and_all_initial_values`). |
| when_running_testsystem_06_without_scalefactor_dense :: should_produce_correct_result | NO | Already in C# (`when_running_testsystem_06_without_scale_factor_dense`). |
| when_running_testsystem_06_without_scalefactor_dense :: should_calculate_comparison_threshold | NO | Already in C# (`when_calculating_comparison_threshold`). |
| when_running_testsystem_06_without_scalefactor_band :: should_produce_correct_result | NO | Band variant; integration test, harness not available. |
| when_running_testsystem_06_with_scalefactor_dense :: should_produce_correct_result | NO | Already in C# (`when_running_testsystem_06_with_scale_factor_dense`). |
| when_running_testsystem_06_with_scalefactor_dense :: should_calculate_comparison_threshold | NO | Already in C# (`when_calculating_comparison_threshold`). |
| when_running_testsystem_06_with_scalefactor_band :: should_produce_correct_result | NO | Band variant; integration test, harness not available. |
| when_running_testsystem_06_setting_all_parameters_as_variable_dense :: should_produce_correct_result | NO | Already in C# (`when_running_testsystem_06_setting_all_parameters_as_variable_dense`). |
| when_running_testsystem_06_setting_all_parameters_as_variable_band :: should_produce_correct_result | NO | Band variant; integration test, harness not available. |
| when_running_testsystem_06_new_schema_without_scalefactor :: should_produce_correct_result | NO | Integration test, harness not available. |
| when_running_testsystem_06_new_schema_with_scalefactor :: should_produce_correct_result | NO | Integration test, harness not available. |
| when_running_testsystem_06_modified_setting_parameter_values_and_initial_values :: should_produce_correct_result | NO | Already in C# (`when_running_testsystem_06_modified_setting_parameter_values_and_initial_values`). |
| when_running_testsystem_06_modified_setting_table_parameter_values :: should_produce_correct_result_without_changing_table_parameter | NO | Already in C# (`when_running_testsystem_06_modified_setting_table_parameter_values`). |
| when_running_testsystem_06_modified_setting_table_parameter_values :: should_produce_correct_result_with_changing_table_parameter | NO | Already in C# (`when_running_testsystem_06_modified_setting_table_parameter_values`). |
| when_running_testsystem_06_V4_modified_setting_parameter_values_and_initial_values :: should_produce_correct_result | NO | Integration test (V4 schema), harness not available. |
| when_running_testsystem_06_V4_modified_setting_table_parameter_values :: should_produce_correct_result_without_changing_table_parameter | NO | Integration test (V4 schema), harness not available. |
| when_running_testsystem_06_V4_modified_setting_table_parameter_values :: should_produce_correct_result_with_changing_table_parameter | NO | Integration test (V4 schema), harness not available. |
| when_running_testsystem_06_new_schema_setting_all_parameters_as_variable :: should_produce_correct_result | NO | Integration test, harness not available. |
| when_running_pksim_input_01 :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_pksim_input_MultiApp_2_dense :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_pksim_input_MultiApp_2_band :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_pkmodelcore_case_study_01 :: mass_balance_at_t0_should_be_ok | NO | Already in C# (`when_running_pkmodelcore_case_study`). |
| when_running_pkmodelcore_case_study_01 :: mass_balance_at_tEnd_should_be_ok | NO | Already in C# (`when_running_pkmodelcore_case_study`). |
| when_running_pkmodelcore_case_study_01 :: amount_observer_for_arterial_blood_plasma_A_should_return_correct_values | NO | Already in C# (`when_running_pkmodelcore_case_study`). |
| when_running_pkmodelcore_case_study_01_with_scalefactor :: mass_balance_at_t0_and_at_tEnd_should_be_ok | NO | Already in C# (`when_running_pkmodelcore_case_study_with_scale_factor`). |
| when_running_pkmodelcore_case_study_01_with_scalefactor :: amount_observer_for_arterial_blood_plasma_A_should_return_correct_values | NO | Already in C# (`when_running_pkmodelcore_case_study_with_scale_factor`). |
| when_running_pkmodelcore_case_study_02 :: mass_balance_at_t0_and_at_tEnd_should_be_ok | NO | Integration test, harness not available. |
| when_running_test4model_reduced02 :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_test4model_reduced02 :: should_redim_variables_and_observers_according_to_is_persistant_flag | NO | Integration test, harness not available. |
| when_loading_from_file_new_schema :: should_be_loaded_from_file | NO | Integration test, harness not available. |
| when_running_below_abstol_test :: all_variable_values_below_abstol_should_be_zero | NO | Already in C# (`when_running_below_absolute_tolerance_test`). |
| when_running_AdultPopulation_sim :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_oral_table_01 :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_loading_from_file_with_infinity_values :: should_be_loaded_from_file | NO | Integration test, harness not available. |
| when_running_IV_EHC :: start_of_gallbladder_refilling_should_be_in_the_switch_startpoints_list | NO | Integration test, harness not available. |
| when_running_Growing_const_tables :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_simulation_with_persistable_parameters :: should_perform_simulation_run_and_return_persistable_parameters_as_observers | NO | Already in C# (`when_running_simulation_with_persistable_parameters`). |
| when_loading_from_file_with_table_formulas :: should_return_table_formula_infos | NO | Already in C# (`when_loading_simulation_with_table_formulas`). |
| when_loading_solver_error_testmodel :: should_load_and_finalize_simulation | NO | Integration test, harness not available. |
| when_changing_ehc_start_time :: changing_ehc_start_time_should_alter_simulation_results | NO | Already in C# (`when_changing_ehc_start_time`). |
| when_loading_from_old_xml_file :: xml_version_should_be_set_to_the_old_version | NO | Managed XML-API test (uses .NET wrapper); out of scope for native gtest. |
| when_loading_from_new_xml_file :: xml_version_should_be_set_to_the_new_version | NO | Managed XML-API test; out of scope for native gtest. |
| when_changing_species_initial_values :: should_update_species_initial_values_in_the_simulation_xml_node | NO | Managed XML-API test; out of scope for native gtest. |
| when_exporting_bcm_platelet_to_matlab :: should_export_to_matlab | NO | Already in C# (`when_exporting_bcm_platelet_to_matlab`). |
| when_loading_simualtion_which_is_not_schema_conform :: should_throw_a_BTS_exception | NO | Managed test (expects a managed exception type); out of scope for native gtest. |
| when_running_simulation_with_if_formula_in_event_condition :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_simulation_returning_not_allowed_negative_values :: should_perform_simulation_run_without_negative_values_check_and_throw_an_exception_with_negative_values_check | NO | Already in C# (`when_running_simulation_returning_not_allowed_negative_values`). |
| when_running_simulation_with_events_simultaneously_increasing_a_variable :: should_perform_all_events | NO | Already in C# (`when_running_simulation_with_events_simultaneously_increasing_a_variable`). |
| when_solving_cvsRoberts_FSA_dns_with_sensitivity_Sensitivity_RHS_function_not_set :: should_solve_example_system_and_return_correct_sensitivity_values | NO | Already in C# (`when_solving_cvsRoberts_FSA_dns_with_sensitivity_Sensitivity_RHS_function_not_set`). |
| when_solving_cvsRoberts_FSA_dns_with_sensitivity_Sensitivity_RHS_function_not_set :: should_solve_example_system_and_return_correct_sensitivity_values_by_entity_path | NO | Already in C# (`when_solving_cvsRoberts_FSA_dns_with_sensitivity_Sensitivity_RHS_function_not_set`). |
| when_running_simulation_with_almost_equal_output_times :: should_remove_duplicate_time_points_according_to_comparison | NO | Already in C# (`when_running_simulation_with_almost_equal_output_times`). |
| when_getting_output_schema :: should_retrieve_correct_output_schema | NO | Managed API test; native `OutputSchemaSpecs` covers schema behaviour separately. |
| when_setting_output_schema :: should_retrieve_output_time_vector_matching_the_new_schema | NO | Managed API test; out of scope for native gtest. |
| when_solving_A_exp_minus_kT_with_sensitivity :: should_solve_example_system_and_return_correct_sensitivity_values | NO | Already in C# (`when_solving_A_exp_minus_kT_with_sensitivity`). |
| when_calculating_sensitivity_of_persistable_parameter :: should_calculate_sensitivity_values_of_persistable_parameter | NO | Already in C# (`when_calculating_sensitivity_of_persistable_parameter`). |
| when_running_GIM_Table_Infusion_starting_at_1000_dense :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_GIM_Table_Infusion_starting_at_1000_band :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_GIM_model_with_negative_Mealtime_offset :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_changing_output_schema :: should_update_output_schema_in_the_simulation_xml_string | NO | Managed XML-API test; out of scope for native gtest. |
| when_getting_simulation_xml_string :: should_return_xml_string_if_keep_xml_option_was_set_to_true | NO | Managed XML-API test; out of scope for native gtest. |
| when_getting_simulation_xml_string :: should_fail_to_return_xml_string_if_keep_xml_option_was_set_to_false | NO | Managed XML-API test; out of scope for native gtest. |
| when_running_simulation_with_ph_solubility_table :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_simulation_with_ph_solubility_table_zero :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_running_simulation_with_ph_solubility_table_const :: should_perform_simulation_run | NO | Integration test, harness not available. |
| when_getting_all_used_parameters_when_identify_used_parameters_set_to_true :: should_return_only_used_parameters_via_native_interface | NO | Already in C# (`when_getting_all_used_parameters_when_identify_used_parameters_set_to_true`). |
| when_getting_all_used_parameters_when_identify_used_parameters_set_to_true :: should_return_only_used_parameters_via_managed_interface | NO | Managed-interface test; already in C#. |
| when_getting_all_used_parameters_when_identify_used_parameters_set_to_false :: should_return_all_parameters_via_native_interface | NO | Already in C# (`when_getting_all_used_parameters_when_identify_used_parameters_set_to_false`). |
| when_getting_all_used_parameters_when_identify_used_parameters_set_to_false :: should_return_all_parameters_via_managed_interface | NO | Managed-interface test; already in C#. |
| when_setting_scale_factor_to_one :: should_solve_the_system_correctly | NO | Already in C# (`when_setting_scale_factor_to_one`). |
