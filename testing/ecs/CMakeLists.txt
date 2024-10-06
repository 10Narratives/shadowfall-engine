# Make ComponentCollection tests
add_executable(ComponentCollectionTesting component-collection.cc)
target_link_libraries(ComponentCollectionTesting engine Catch2::Catch2)

# Nake Archetype tests
add_executable(ArchetypeTesting archetype.cc)
target_link_libraries(ArchetypeTesting engine Catch2::Catch2)

# Make EntityID tests
add_executable(EntityIDTesting archetype.cc)
target_link_libraries(EntityIDTesting engine Catch2::Catch2)